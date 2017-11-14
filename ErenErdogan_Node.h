#pragma once

#ifndef ERENERDOGAN_NODE_H
#define ERENERDOGAN_NODE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Node {
	friend class LinkedList;
public:
	Node(string& symbol, double price, int quant);
	

	Node()
	{
		stock_symbol = "";
		stock_price = 0.0;
		stock_quant = 0;
		stock_total = 0;

		this->next = NULL;
		this->prev = NULL;
	}

	void setSymbol(string);
	string getSymbol();

	void setPrice(double);
	double getPrice();

	void setQuant(int);
	double getQuant();

	void setTotal(double);
	double getTotal();

	void clear();

protected:
	string stock_symbol;
	double stock_price;
	int stock_quant;
	double stock_total;
	
	Node *next;
	Node *prev;
};

#endif