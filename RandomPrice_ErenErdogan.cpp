#include "RandomPrice_ErenErdogan.h"

Random_Price::Random_Price()
{
	//Stock Names Vector
	vector<string> stock_symbol = {};

	//Stock Prices Vector1, for Results_1.txt
	vector<double> stock_price1 = {};

	//Stock Prices Vector2, for Results_2.txt
	vector<double> stock_price2 = {};


}

Random_Price::~Random_Price()
{
}


void Random_Price::setVectors(vector<string> symbol, vector<double> price1, vector<double> price2)
{
	//Input values for vectors to store stock information

	stock_symbol.swap(symbol);

	stock_price1.swap(price1);

	stock_price2.swap(price2);


}


double Random_Price::getStockPrice(string symbol)
{

	int i = 0;


	while (i < stock_symbol.size()) {
		if (stock_symbol[i] == symbol)
		{
			return getRandomPrice(i);
		}
		i++;

	}

	// If this point reached means symbol not available
	return -1;



}

double Random_Price::getRandomPrice(int index)
{
	srand(time(NULL));

	int x = 0;

	x = rand() % 2;

	if (x == 0) {
		return stock_price1[index];
	}

	else
	{
		return stock_price2[index];
	}

}
