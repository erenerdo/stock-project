#include "BankAccount_ErenErdogan.h"

Bank::Bank()
{

	
}

Bank::~Bank()
{
}

void Bank::deposit(double money, LinkedList & list)
{

	setBalance(getBalance() + money);

	string event = "Deposit";

	write_to_history(event, money, "DATE", getBalance() );

	WriteGraphData(list);

}

void Bank::withdraw(double money, LinkedList & list)
{
	if (money > getBalance()) {

		cout << "Insufficient Funds!" << endl
			<< "You only have $" << getBalance() << " in your account" << endl << endl;
		}
	else {
		setBalance(getBalance() - money);
		}

	string event = "Withdraw";

	write_to_history(event, money, "DATE", getBalance());

	WriteGraphData(list);

}

void Bank::view_bank_account(LinkedList & list)
{

	cout << "\nYou have $" << getBalance() << " in your bank account" << endl << endl;

	WriteGraphData(list);

}

void Bank::print_history()
{

	cout << "Bank Account Transaction History:" << endl;

	cout << left << setw(15) << "Event" << setw(20) << "Amount($)" << setw(20) << "Date" << setw(20) << "Balance($)"  << endl;

	fstream inputFile;

	inputFile.open("bank_transaction_history.txt");

	string event = "";
	double amount = 0;
	string date = "";
	double balance = 0;

	while (inputFile >> event >> amount >> date >> balance) {

		cout << left << setw(15) << event << setw(20) << fixed << setprecision(2)<< amount << setw(20) << date << setw(20) << fixed << setprecision(2) << balance  << endl;
	}

	cout << endl;

	inputFile.close();

}

void Bank::write_to_history(string event, double amount, string date, double balance)
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

	output.close();

}

void Bank::read_cash()
{
	fstream inputFile;

	inputFile.open("bank_transaction_history.txt");

	string event = "";
	double amount = 0;
	string date = "";
	double balance = 10000;

	while (inputFile >> event >> amount >> date >> balance) {

		
	}

	setBalance(balance);

}
