#pragma once

#ifndef BANKACCOUNT_ERENERDOGAN_H
#define BANKACCOUNT_ERENERDOGAN_H


#include "ErenErdogan_Node.h"
#include "ErenErdogan_LinkedList.h"
#include "Account_ErenErdogan.h"

class Bank : public Account {

public:
	Bank();
	void deposit(double, LinkedList & list);
	void withdraw(double, LinkedList & list);
	~Bank();
	void view_bank_account(LinkedList & list);
	void print_history();
	void write_to_history(string event, double amount, string date, double balance);

	void read_cash();

	Account a;
};

#endif // !