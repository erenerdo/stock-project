#include "StockAccount_ErenErdogan.h"

Stock::Stock()
{
	

}

Stock::~Stock()
{
}



void Stock::insert_stock_node( Node & stock, LinkedList & portfolio, string symbol, double price, int quant)
{
	stock.clear();
	stock.setSymbol(symbol);
	stock.setPrice(price);
	stock.setQuant(quant);
	stock.setTotal(stock.getQuant());

	portfolio.addToList(&stock);

}






void Stock::MakePurchase( string symbol, double price, int quant, LinkedList & list, Random_Price & r)
{
	string event = "BUY";
	// Check to see if symbol is available

	if (r.getStockPrice(symbol) == -1 || quant < 0) {

		cout << "\nThat stock is not available or there's an error in your input! Transaction Failed" << endl << endl;

	}

	// symbol found
	else {
		// Check to see if live stock price is greater than amount willing to pay

		double live_price = 0;
		live_price = r.getStockPrice(symbol);

		if (live_price > price) {
			
			cout << "\nStock price greater than you are willing to pay! Transaction Failed" << endl << endl;
			
		}

		else {
			// price willing to pay higher than actual stock price

			// Check to see if person has enough cash

			if ( (live_price * quant) > getBalance() )
			{
				cout << "\nYou dont have enough cash to make this purchase! Transaction Failed" << endl << endl;
			}

			else {

				

				

				// All purchase checks have passed
				cout << "\nYou have purchased " << quant << " share(s) of " << symbol << " at $" << fixed << setprecision(2) <<live_price
					<< " each for a total of $" << fixed << setprecision(2)<<  quant * live_price << endl << endl;


				// Subtract purchase from cash balance

				setBalance( (getBalance() - (quant * live_price)) );

				BankTransactionWrite( event, (live_price)*quant, "1", getBalance() );

				cout << "New cash balance is $" << getBalance() << endl;

				// Insert new stock purchase in portfolio
				
				// Check to see if stock is already in portfolio

				// if yes, update with new purchase 
				if ( list.isInList(symbol) ) {		 

				// If yes then in order to maintain the sorted order, we will create 
				// new updated variables for symbol, quant, price (taken from random price/live purchase price)
				// then remove the old node and input a new node with the updated values

					StockTransactionWrite(event, symbol, live_price, quant, (live_price*quant));

					//update quantity
					list.updateQuant(symbol, quant);

					//remove old node from list
					list.removeNodeFromListNo(symbol);

					//insert new node with updated quantiy and current price

					Node node(symbol, live_price, quant);
					list.addToList(&node);

					

					//string event, string symbol, double price, int quant, double total
					WriteGraphData(list);

					list.printList();

				}

				// if no, add to linked list
				else {		
					Node node(symbol, live_price, quant);

					list.addToList(&node);

					StockTransactionWrite(event, symbol, live_price, quant, (live_price*quant) );

					WriteGraphData(list);

					list.printList();


				}

				
				
			}

				
		}
	}
	

}

void Stock::SellShares(string symbol, double price, int quant, LinkedList & list, Random_Price & r)
{
	string event = "SELL";
	// check to see if stock is in portfolio (linked list)

	if (list.isInList(symbol) && quant > 0)

	{	
		// stock in portfolio passed

		// check to see if they have enough quantity to sell

		int portfolio_quant = 0;
		portfolio_quant = list.getQuant(symbol);

		if (quant > portfolio_quant) {

			cout << "\nYou can't sell more than you own! Transaction failed." << endl << endl;
		}
		else {

			// portfolio_quant greater than amount wanting to sell

			// check to see if their minimum price to sell is lower than the live price

			double live_price = r.getStockPrice(symbol);

			if (live_price > price)
			{

				// All transaction checks pass

				StockTransactionWrite(event, symbol, live_price, quant, (live_price*quant));

				// update quantity

				int new_quant = 0;
				new_quant = portfolio_quant - quant;

					// if quantity > 0, pass in new quantity

				if (new_quant > 0) {


					// remove old node
					list.removeNodeFromListNo(symbol);

					// create new node with new quantity and live price
					Node node(symbol, live_price, new_quant);

					// add new node to list
					list.addToList(&node);

					//Update stock transactions file

					
					
				}

				else {
					// new quant must be zero then
					
					// remove old node
					list.removeNodeFromListNo(symbol);

					// update stock transactions file
				
				}

				// update cash balance

				setBalance((getBalance()) + (quant*live_price));

				BankTransactionWrite(event, (live_price)*quant, "1", getBalance());

				WriteGraphData(list);

				cout << "\nYou have sold " << quant << " share(s) of " << symbol << " at $" << fixed << setprecision(2) << live_price
					<< " each for a total of $" << fixed << setprecision(2) << quant * live_price << endl << endl;

				cout << "New cash balance is $" << getBalance() << endl;

				list.printList();

			}

			else
			{
				cout << "\nLive stock price of $"<< fixed << setprecision(2) << live_price <<   " below your minimum per share to sell. Transaction failed." << endl << endl;
			}
		}
	}


	else {
		cout << "\nThis stock is not in your portfolio or there's an error in your input! Transaction failed." << endl << endl;
	}
	

	// check to see if their minimum price to sell is lower than the live price








}

void Stock::StockTransactionWrite( string event, string symbol, double price, int quant, double total)
{

	int hour = 0;
	int minute = 0;
	int second = 0;
	int day = 0;
	int jourSemain = 0;
	int month = 0;
	int year = 0;

	Time(hour, minute, second, day, month, year);
	
	ofstream output;

	output.open("stock_transaction_history.txt", std::ios::app);
		

	output << event << "\t" << symbol << "\t" << quant << "\t" << price << "\t" << total << "\t"<< hour << ":" << minute << ":" << second << endl;
	



}

void Stock::BankTransactionWrite(string event, double amount, string date, double balance)
{
	

	int hour = 0;
	int minute = 0;
	int second = 0;
	int day = 0;
	int jourSemain = 0;
	int month = 0;
	int year = 0;

	Time(hour, minute, second, day, month, year);



	ofstream output;

	output.open("bank_transaction_history.txt", std::ios::app);
	

	output << event << "\t" << amount << "\t" << month << "/" << day << "/" << year << "\t" << balance << endl;





}

void Stock::PrintTransactionHistory()
{
	cout << endl << "Stock Transaction History" << endl;
	
	cout << left << setw(15) << "Event" << setw(20) << "CompSymbol" << setw(20) << "Quantity" << setw(20) << "PricePerShare" << setw(20) << "TotalValue" << setw(20) << "Time" << endl;
	
	fstream inputFile;

	inputFile.open("stock_transaction_history.txt");

	string event = "";
	string symbol = "";
	int quant = 0;
	double price = 0;
	double total = 0;
	string time = "";

	while (inputFile >> event >> symbol >> quant >> price >> total >> time) {

		cout << left << setw(15) << event << setw(20) << symbol << setw(20) << quant << setw(20) << price << setw(20) << total << setw(20) << time << endl;
	}
	
	cout << endl;

	inputFile.close();

}



