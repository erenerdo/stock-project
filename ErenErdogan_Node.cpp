#include "ErenErdogan_Node.h"


Node::Node(string & symbol, double price, int quant)
	:stock_symbol(symbol), stock_price(price), stock_quant(quant)
{
	setTotal((stock_quant));
	this->next = NULL;
	this->prev = NULL;

}

void Node::setSymbol(string symbol)
{
	stock_symbol = symbol;
}

string Node::getSymbol()
{
	return stock_symbol;
}

void Node::setPrice(double price)
{
	stock_price = price;
}

double Node::getPrice()
{
	return stock_price;
}

void Node::setQuant(int quant)
{
	stock_quant = quant;
}

double Node::getQuant()
{
	return stock_quant;
}

void Node::setTotal(double quant)
{

	stock_total = (quant * stock_price);
}

double Node::getTotal()
{
	return stock_total;
}

void Node::clear()
{
	stock_symbol = "";
	stock_price = 0.0;
	stock_quant = 0;
	stock_total = 0;
}

