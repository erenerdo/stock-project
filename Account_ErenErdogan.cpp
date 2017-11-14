#include "Account_ErenErdogan.h"




Account::Account()
{
	//Stock Names Vector
	vector<double> TotalValueData = {};

	//Stock Prices Vector1, for Results_1.txt
	vector<double> TotalValIndex = {};

}

Account::~Account()
{
}

void Account::setBalance(double balance)
{
	cash_balance = balance;

}

double Account::getBalance()
{
	return cash_balance;
}

void Account::Time(int &hour, int &minute, int &second, int &day, int &month, int &year)
{
	time_t rawtime;
	struct tm timeinfo;  // no longer a pointer

	time(&rawtime);

	// on platforms with POSIX localtime_r but no localtime_s, add this macro
	// #define localtime_s(x, y) localtime_r(y, x)
	localtime_s(&timeinfo, &rawtime); // fills in your structure,
									  // instead of returning a pointer to a static one

	hour = timeinfo.tm_hour;  // no longer using a pointer
	minute = timeinfo.tm_min;
	second = timeinfo.tm_sec;
	day = timeinfo.tm_mday;
	
	month = timeinfo.tm_mon + 1;
	year = timeinfo.tm_year + 1900;

	

}


void Account::Graph()
{
	TotalValueData.clear();
	TotalValIndex.clear();

	ifstream inputGraphData;

	inputGraphData.open("Graph_Data.txt");

	double TotalVal = 0;

	while (inputGraphData >> TotalVal) {

		TotalValueData.push_back(TotalVal);
	}

	for (unsigned int i = 0; i < TotalValueData.size() ; i++) {

		TotalValIndex.push_back(i + 1);
	}


	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL) {

		cout << "Error: Not Found" << endl;
		exit(1);
	}

	

	double* x_val = new double[TotalValueData.size()];

	double* y_val = new double[TotalValueData.size()];

	for (unsigned int i = 0; i < TotalValueData.size(); i++) {

		y_val[i] = TotalValueData[i];
		x_val[i] = TotalValIndex[i];
	}

	
	const int arraysize = TotalValueData.size();
	
	for (unsigned int i = 0; i < TotalValueData.size(); i++) {

		cout << x_val[i] << "\t" << y_val[i] << endl;
		
	}


	mxArray* SIN = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	memcpy((void *)mxGetPr(SIN), (void *)y_val, sizeof(double)*arraysize);
	engPutVariable(ep, "Y", SIN);

	

	mxArray* DEG = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	memcpy((void *)mxGetPr(DEG), (void *)x_val, sizeof(double)*arraysize);
	engPutVariable(ep, "X", DEG);

	engEvalString(ep, "figure('units', 'normalized','outerposition', [0 0 1 1]),");
	engEvalString(ep, "plot (X, Y, 'r'), grid minor, title(' Total Portfolio Value'),");
	engEvalString(ep, "xlabel('Time'), ylabel('Total Portfolio Value ($)')");
	engEvalString(ep, "set(gca,'YTickLabel',num2str(get(gca,'YTick').'))");
	engEvalString(ep, "axis([-inf,inf,0,inf])");

	
	
}

void Account::WriteGraphData(LinkedList & port)
{
	ofstream outputGraphData;

	// open data and start writing to the end of the file
	outputGraphData.open("Graph_Data.txt", std::ios::app);

	double TotalVal = 0;

	// write 10 sets of data to simulate a time frame
	for (int i = 0; i < 25; i++)
	{
		// Get total Portfolio + Cash Balance
		TotalVal = GetTotalPortVal(port);

		// Output the data to a text file
		outputGraphData << TotalVal << endl;

		// Update with live prices to simulate live stock price changing
		port.updateWithLivePrices();
	}

	// close text file
	outputGraphData.close();

}

double Account::GetTotalPortVal(LinkedList & port)
{
	// return portfolio + cash balance value
	return (port.totalPortfolioValue() + getBalance() );
}

