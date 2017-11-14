#pragma once



#ifndef ERENERDOGAN_LINKEDLIST_H
#define ERENERDOGAN_LINKEDLIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "ErenErdogan_Node.h"
#include "RandomPrice_ErenErdogan.h"



class LinkedList :public Random_Price {
public:
	LinkedList(Random_Price & ra);
	~LinkedList();

	// Function to add a snode (stock) to portfolio
	void addToList(Node *);
	
	// Function to print portfolio
	void printList();

	// Function to remove a node (stock) from the portfolio
	void removeNodeFromListNo(string);

	// Function that checks to see if a stock is already in portfolio
	bool isInList(string symbol);

	// Function that updates the quantity value 
	void updateQuant(string symbol, int &quant);

	// Function that checks if the list is empty
	bool isEmpty() const;

	// Function that will update each nodes price with the live (random) value that it is acquiring from Random_Price Class
	// Will be used everytime the portfolio is asked to be viewed
	void updateWithLivePrices();

	double totalPortfolioValue();

	int getQuant(string symbol);

	// Function to write to a text file to keep track of the live portfolio
	// same text file will be used to load in previous portfolio information

	void write_live_portfolio();
	

	// Function used to update the sort after the live price have been inputted since the total amounts now are different and the sort could be out of order
	void updateSort();

private:
	Node *firstPtr;
	Node *lastPtr;
	Random_Price r;
};

#endif
