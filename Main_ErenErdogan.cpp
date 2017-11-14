// Eren Erdogan
// RU ID: 125008327
// Final Project

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <time.h>

#include "ErenErdogan_Node.h"
#include "ErenErdogan_LinkedList.h"
#include "StockAccount_ErenErdogan.h"
#include "BankAccount_ErenErdogan.h"
#include "RandomPrice_ErenErdogan.h"


using namespace std;


// Design Pattern Templeate Implementation for Printing

//Create base template
class Base {

	// Place Holder Function for printing menu description

	virtual void ph1() = 0;

public:
	void print_menu() {

		ph1();
	}


};

class Main_Menu : public Base {

	virtual void ph1() {

		cout << "Please select an account to access:" << endl
			<< "1. Stock Portfolio Account" << endl
			<< "2. Bank Account" << endl
			<< "3. Exit" << endl << endl
			<< "Option: ";

	}

};

class Stock_Menu : public Base {

	virtual void ph1(){
		cout << "Please select an option:" << endl
			<< "1. Display the price for a stock symbol" << endl
			<< "2. Display the current portfolio" << endl
			<< "3. Buy Shares" << endl
			<< "4. Sell Shares" << endl
			<< "5. View a graph for the portfolio value" << endl
			<< "6. View transaction history" << endl
			<< "7. Return to previous menu" << endl << endl
			<< "Option: ";

	}

};

class Bank_Menu : public Base {

	virtual void ph1() {

		cout << "1. View account balance" << endl
			<< "2. Deposit money" << endl
			<< "3. Withdraw money" << endl
			<< "4. Print out history" << endl
			<< "5. Return to previous menu" << endl << endl
			<< "Option: ";

	}

};




void file_open(vector<string>& stock_names, vector<double>& prices_1, vector<double>& prices_2);



//Create vectors to store stock names and prices

//Stock Names Vector
vector<string> stock_names = {};

//Stock Prices Vector1, for Results_1.txt
vector<double> price_1 = {};

//Stock Prices Vector2, for Results_2.txt
vector<double> price_2 = {};



Account a;

Node node;

Bank bank;

Random_Price r;

Stock stock;

double Account::cash_balance = 10000;

void load_portfolio( LinkedList & list);

int main() {

	// Read bank transactions history and update cash balance with more recent saved value
	bank.read_cash();
	
	file_open(stock_names, price_1, price_2);

	r.setVectors(stock_names, price_1, price_2);

	// initialize linked list, pass in values for pricing
	LinkedList portfolio(r);

	// load saved portfolio values
	load_portfolio(portfolio);

	int main_menu_choice = 0;
	int quit_main = 1;
	
	cout << "Welcome to the Account Management System." << endl;

	Main_Menu menu1;

	Stock_Menu menu2;

	Bank_Menu menu3;

	Base* array[] = { &menu1, &menu2, &menu3 };

	Random_Price random;
	
	string string_inpt = "";

	double stock_price = 0;

	int int_inpt = 0;


	
	while (quit_main) {


		array[0]->print_menu();

		//print main menu
		cin >> main_menu_choice;

		switch (main_menu_choice) {
		
		case 1:
		{
			int stock_menu_choice = 0;
			int quit_stock = 1;

			cout << "Stock Portfolio Account Menu" << endl << endl;
			
			

			while (quit_stock) {


				//print stock menu
				array[1]->print_menu();

				cin >> stock_menu_choice;

				switch (stock_menu_choice) {
					
				case 1:
				{
					cout << "You choose: Diplay the price for a stock symbol" << endl
						<< "Please enter the stock symbol: " << endl;
					cin >> string_inpt;

					stock_price = r.getStockPrice(string_inpt);

					if (stock_price == -1)
					{
						cout << "That stock is not available or does not exit!" << endl << endl;
					}

					else
					{
						cout << "Price per share of " << string_inpt << ": $" << stock_price << endl << endl;
					}
				}
				break;

				case 2:
				{
					cout << "You choose: Display Current Portfolio. "  << endl;

					portfolio.printList();
				}
				break;

				case 3:
				{
					cout << "You choose option: Buy Shares" << endl;

					cout << "Pleaes enter the stock symbol you wish to purchase: ";
					cin >> string_inpt;

					cout << "Please enter the number of shares you'd like to buy: ";
					cin >> int_inpt;

					cout << "Please enter the maximum amount you are willing to pay per share: ";
					cin >> stock_price;

					stock.MakePurchase(string_inpt, stock_price, int_inpt, portfolio, r);

					portfolio.write_live_portfolio();

				}
				break;

				case 4:
				{
					cout << "You choose option: Sell Shares" << endl;

					cout << "Pleaes enter the stock symbol you wish to sell: ";
					cin >> string_inpt;

					cout << "Please enter the number of shares you'd like to sell: ";
					cin >> int_inpt;

					cout << "Please enter the minimum amount you are willing to sell each share for: ";
					cin >> stock_price;

					stock.SellShares(string_inpt, stock_price, int_inpt, portfolio, r);

					portfolio.write_live_portfolio();

				}
				break;

				case 5:
				{
					cout << "You choose option: View Graph " << endl << endl;

					a.Graph();

				}
				break;

				case 6:
				{
					cout << "You choose option: Print Transaction History" << endl;

					stock.PrintTransactionHistory();
				}
				break;

				case 7:
				{
					cout << "You choose to go back to the previous menu. " << endl;
					quit_stock = 0;
				}
				break;

				default:
				{
					cout << "Invalid input, try again" << endl;
					
				}
				break;

				}
			}

		}
		break;

		case 2:
		{
			int bank_menu_choice = 0;
			int quit_bank = 1;

			cout << "Bank Account Menu" << endl << endl;
			

			while (quit_bank) {

				//print bank menu
				array[2]->print_menu();

				cin >> bank_menu_choice;

				double cash_flow = 0;

				switch (bank_menu_choice) {


				case 1:
				{
					cout << "You choose: View Account" << endl;

					bank.view_bank_account(portfolio);
				}
				break;

				case 2:
				{
					cout << "You choose Deposit " << endl << endl;
					cout << "Please enter the amount you'd like to deposit" << endl;
					cin >> cash_flow;

					if (cash_flow < 0) {

						cout << "Can not deposit negative cash!" << endl << endl;
					}
					else {
						bank.deposit(cash_flow, portfolio);

						cout << "You've deposited $" << fixed << setprecision(2) << cash_flow << endl << endl;
					}
				}
				break;

				case 3:
				{
					cout << "You choose Withdraw " << endl << endl;
					cout << "Please enter the amount you'd like to deposit" << endl;

					cin >> cash_flow;

					if (cash_flow < 0) {

						cout << "Can not withdraw negative cash!" << endl << endl;
					}
					else {
						bank.withdraw(cash_flow, portfolio);

						cout << "You've withdrawn $" << fixed << setprecision(2) << cash_flow << endl;
					}
				}
				break;

				case 4:
				{
					cout << "You choose Print History" << endl << endl;

					bank.print_history();

				}
				break;

				case 5:
				{
					cout << "You choose to return to the previous menu"<< endl << endl;
					quit_bank = 0;
				}
				break;

				default:
				{
					cout << "Invalid Entry! Going back to main menu." << endl;
					quit_bank = 0;
				}
				break;
				}

			}
		}
		break;
		case 3:
		{
			cout << "Program Exiting. Good Bye!" << endl;
			quit_main = 0;
		}
		break;

		default:
		{
			cout << "Invalid Input, Program Exiting." << endl;
			quit_main = 0;

		}
		break;

		}

	} // End While Loop Main Menu
	
}



void file_open(vector<string>& stock_names, vector<double>& prices_1, vector<double>& prices_2) {

	ifstream inFile1;
	inFile1.open("Result_1.txt");

	ifstream inFile2;
	inFile2.open("Result_2.txt");

	//Check For Error

	if (inFile1.fail()) {

		cerr << "Error Opening File" << endl;
		exit(1);
	}

	string symbol = "";
	double price = 0;
	string date = "";

	while (inFile1 >> symbol >> price >> date) {

		stock_names.push_back(symbol);
		prices_1.push_back(price);

	}
	
	stock_names.clear();

	while (inFile2 >> symbol >> price >> date) {

		stock_names.push_back(symbol);
		prices_2.push_back(price);

	}

	inFile1.close();
	inFile2.close();
}

void load_portfolio(LinkedList & list)
{

	ifstream f;

	f.open("live_portfolio.txt");

	string sym = "";
	int quant = 0;
	double price = 0;
	double total = 0;

	while (f >> sym >> quant >> price >> total)
	{

		Node node(sym, price, quant);

		list.addToList(&node);
		
	}

	f.close();
}

