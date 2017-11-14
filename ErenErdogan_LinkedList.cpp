#include "ErenErdogan_LinkedList.h"
#include <string>
#include <iomanip>

LinkedList::LinkedList(Random_Price & ra)
{
	r = ra;
	firstPtr = NULL;
	lastPtr = NULL;

	
}

LinkedList::~LinkedList()
{
	Node *temp;
	while (firstPtr != 0)
	{
		temp = firstPtr;
		firstPtr = firstPtr->next;
		delete temp;
	}

}



void LinkedList::addToList(Node *element)
{
	Node *temp = new Node;

	temp->stock_price = element->stock_price;
	temp->stock_quant = element->stock_quant;
	temp->stock_symbol = element->stock_symbol;
	temp->stock_total = element->stock_total;


	if (isEmpty()) {
		firstPtr = temp;
		lastPtr = temp;
		}

	// If only 1 element in list
	else if (firstPtr == lastPtr) {

		if (temp->stock_total <= firstPtr->stock_total) {
			
			// Add to end of list
			temp->prev = firstPtr;
			firstPtr->next = temp;
			lastPtr = temp;

		}

		else
		{
			// Add to front of list
			temp->next = firstPtr;
			firstPtr->prev = temp;
			firstPtr = temp;

		}

	}

	else {
		Node *currentPtr = new Node;
		currentPtr = firstPtr;

		while ( ((temp->stock_total) <= (currentPtr->stock_total)) && (currentPtr != lastPtr) ){
				
			currentPtr = currentPtr->next;
			
		}


		//Adding to the front of the list
		if (currentPtr->prev == NULL) {
				temp->next = currentPtr;
				currentPtr->prev = temp;
				firstPtr = temp;
			}

		//Adding to the end of the list
		else if (currentPtr == lastPtr){
			temp->prev = currentPtr;
			currentPtr->next = temp;
			lastPtr = temp;

		}

		//Adding in the list
		else {

			// Update new node branches
			temp->next = currentPtr;
			temp->prev = (currentPtr->prev);

			// Update old nodes branches
			(currentPtr->prev)->next = temp;
			currentPtr->prev = temp;


		}


		} //End else when list is not empty

}



	
void LinkedList::printList()
{
	
	
	if (isEmpty()) {

		cout << "\nYour portfolio is empty" << endl << endl;
	}
	else {

		updateWithLivePrices();

		updateSort();

		Node *currentPtr = firstPtr;

		cout << endl << "Stock Portfolio" << endl;

		cout << left << setw(20) << "Stock Symbol";
		cout << setw(20) << "Stock Price($)";
		cout << setw(20) << "Quantity";
		cout << setw(20) << "Stock Total Value($)";
		cout << endl;

		while (currentPtr != NULL) {

			cout << left << setw(20) << currentPtr->stock_symbol;
			cout << setw(20) << fixed << setprecision(2)  << currentPtr->stock_price;
			cout << setw(20) << currentPtr->stock_quant;
			cout << setw(20) <<  fixed << setprecision(2) << currentPtr->stock_total;
			cout << endl;

			

			currentPtr = currentPtr->next;
		}

		cout << "Portfolio Value: $" << fixed <<setprecision(2) << totalPortfolioValue() << endl;

		cout << endl;

	}
	
}





void LinkedList::removeNodeFromListNo(string symbol)
{
	if (firstPtr != NULL) {

		Node *temp = firstPtr;

		if (firstPtr == lastPtr && (symbol == firstPtr->stock_symbol) ) {

			firstPtr = NULL;
			lastPtr = NULL;
			delete temp;
		}

		else {
			// If need to delete first node
			if (symbol == firstPtr->stock_symbol)
			{
				(firstPtr->next)->prev = NULL;
				firstPtr = firstPtr->next;
				delete temp;
			}

			else {
				while (temp->next != NULL && (!(symbol == temp->next->stock_symbol)))
				{
					temp = temp->next;
				}

				Node *target = temp->next;

				// not last element in list
				if ((target->next != NULL) && (target != NULL)) {



					temp->next = target->next;
					(target->next)->prev = temp;



					delete target;
				}

				// Last element in list
				else if (target->next == NULL) {
					temp->next = NULL;
					lastPtr = temp;

					delete target;

				}

				else if (target == NULL) {

					cout << "Item Not Found!!" << endl;
				}

				else {
					cout << endl;
				}

			}
		}
	}
	
}

bool LinkedList::isInList(string symbol)
{
	if (isEmpty())
	{
		return false;
	}
	 // list is not empty
		Node *temp = firstPtr;


		// List only has 1 element
	if (firstPtr == lastPtr) {
		if ( symbol == (temp->stock_symbol) )
			return true;
		else
			return false;
		}
		// List has more than 1 element
	else {
		while (temp != NULL)
		{
			if ( (temp->stock_symbol) == symbol)
			{
				return true;
			}

			temp = temp->next;
		}
		return false;
	}


	
}

void LinkedList::updateQuant(string symbol, int &quant)
{
	// This function will only run when list is not empty
	Node *temp = firstPtr;

	
	
	while (temp != NULL)
		{
			if ((temp->stock_symbol) == symbol)
			{
				quant = (quant + (temp->stock_quant) );
				break;
			}

			temp = temp->next;
		}

	



}



bool LinkedList::isEmpty() const
{
	return firstPtr == NULL;
}

void LinkedList::updateWithLivePrices()
{
	// start at first node
	Node *temp = firstPtr;


	while (temp != NULL) {

		// Go through whole list and change price to live value to simulate stock prices changing in real time

		// update price with live (random) price
		temp->stock_price = r.getStockPrice(temp->stock_symbol);

		// update stocks total value now with updated price
		temp->stock_total = (temp->stock_quant *temp->stock_price);

		temp = temp->next;

	}




}

double LinkedList::totalPortfolioValue()
{
	// start at first node
	Node *temp = firstPtr;

	double total = 0;

	while (temp != NULL) {

		total += temp->stock_total;

		temp = temp->next;

	}

	return total;
}

int LinkedList::getQuant(string symbol)
{
	// start at first node
	Node *temp = firstPtr;


	while (temp != NULL) {

		// check to see if current node is stock
		if (symbol == (temp->stock_symbol))
		{
			// if so return quant
			return temp->stock_quant;
		}

		// if not continue to next
		temp = temp->next;
	}

	// stock not found

	return -1;

}

void LinkedList::write_live_portfolio()
{
	
	ofstream f;

	// Opens live portfolio and clears all data
	f.open("live_portfolio.txt", std::ofstream::out | std::ofstream::trunc);
	

	
	// start at first node
	Node *temp = firstPtr;
	
	// write data
	while ( (temp != NULL) )
	{
		f << (temp->stock_symbol) << "\t"<< (temp->stock_quant) << "\t" << (temp->stock_price) << "\t" << (temp->stock_total) << endl;
			// go to next node
		temp = temp->next;
	}
	
	
	// close file
	f.close();




}

void LinkedList::updateSort()
{
	// start at first node
	Node *temp = firstPtr;

	while ((temp != NULL) && (temp->next != NULL) ) {

		if (temp->stock_total < ((temp->next)->stock_total))

		{
			string symbol = temp->stock_symbol;

			int quant = temp->stock_quant;

			double price = temp->stock_price;

			removeNodeFromListNo(symbol);;

			Node element(symbol, price, quant);

			addToList(&element);

			temp = firstPtr;
		}
	
		else
		{
			temp = temp->next;
		}
	
	}


}

