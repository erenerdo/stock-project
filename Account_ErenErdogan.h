#pragma once

#ifndef ACCOUNT_ERENERDOGAN_H
#define ACCOUNT_ERENERDOGAN_H





#include "ErenErdogan_Node.h"
#include "ErenErdogan_LinkedList.h"
#include "RandomPrice_ErenErdogan.h"

#include <yvals.h>
#if (_MSC_VER > 1600)
#define __STD_UTF_16__
#endif
#include "mex.h"
#include <cmath>
#include <string>



#include <engine.h>

#pragma comment (lib , "libmx.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libeng.lib")



class Account : public Random_Price {

	static double cash_balance;

public:
	Account();
	virtual ~Account();
	void setBalance(double);
	double getBalance();

	void Time(int &hour, int &minute, int &second, int &day, int &month, int &year);

	// MATLAB Graph
	void Graph();

	void WriteGraphData(LinkedList & port);

	double GetTotalPortVal(LinkedList & port);

	//Stock Names Vector
	vector<double> TotalValueData;

	//Stock Prices Vector1, for Results_1.txt
	vector<double> TotalValIndex;

};

#endif // !ACCOUNT_ERENERDOGAN_H