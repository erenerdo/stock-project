#pragma once

#ifndef STOCKACCOUNT_ERENERDOGAN_H
#define STOCKACCOUNT_ERENERDOGAN_H


#include "ErenErdogan_Node.h"
#include "ErenErdogan_LinkedList.h"
#include "Account_ErenErdogan.h"

#include <iomanip>
#include <ctime>


class Stock : public Account {

public:
	Stock();
	~Stock();


	void insert_stock_node(Node & stock, LinkedList & portfolio, string symbol, double price, int quant);
	

	void MakePurchase(string symbol, double price, int quant, LinkedList & list, Random_Price & r);

	void SellShares(string symbol, double price, int quant, LinkedList & list, Random_Price &r);
	
	void StockTransactionWrite(string event , string symbol, double price, int quant, double total);

	void BankTransactionWrite(string event, double amount, string date, double balance);

	void PrintTransactionHistory();


	


protected:

	// Total portfolio value
	double TotalPortVal;

	//Stock Names Vector
	vector<double> TotalValueData;

	//Stock Prices Vector1, for Results_1.txt
	vector<double> TotalValIndex;

	

};


#endif