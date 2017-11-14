#pragma once


// This class is an adapter design pattern

// Client is inputting multiple price vectors, and we will use this class to return 1 random price
// Saves time and will elimnate having to add vectors to multiple classes and therefore waste memory
// This class can also easily and quickly be modified to include more stock prices also

#ifndef RANDOMPRICESTRATEGY_ERENERDOGAN_H
#define RANDOMPRICESTRATEGY_ERENERDOGAN_H

#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>     
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <fstream>



using namespace std;


class Random_Price {

public:
	Random_Price();
	~Random_Price();

	void setVectors(vector<string> symbol, vector<double> price1, vector<double> price2);


	double getStockPrice(string symbol);


	double getRandomPrice(int index);



	//Stock Names Vector
	vector<string> stock_symbol;

	//Stock Prices Vector1, for Results_1.txt
	vector<double> stock_price1;

	//Stock Prices Vector2, for Results_2.txt
	vector<double> stock_price2;
};



#endif