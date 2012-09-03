#include <fstream>

#include "User.h"

using namespace std;


// Singleton Utilities
User * User::mInstance = NULL;

User * User::getInstance() {
	if(mInstance == NULL)
		mInstance = new User();

	return mInstance;
}

// Serialization Utilities
bool User::serializePortfolio() {
	int n = portfolio.size();

	// We want to overwrite the file if it exists too
	ofstream out("save_p.cab", ios::binary);
	
	if(!out)
		return false;
	
	out << n;

	for(vector<Quote>::iterator i = portfolio.begin(); i != portfolio.end(); ++i) {
		Quote::QuoteSerialized obj = i->serialize();
		out.write((char *)&obj, sizeof(obj));
	}

	out.close();
	return true;
}

User::UserSerialized User::serializeUser() {
	UserSerialized obj;
	
	obj.cashInHand = cashInHand;
	obj.stockWorth = stockWorth;
	obj.totalWorth = totalWorth;
	strcpy(obj.name, name.c_str());

	return obj;
}

bool User::serialize() {
	ofstream out("save_u.cab", ios::binary);

	// File failed to open
	if(!out)
		return false;

	// Portfolio failed to serialize
	if(!serializePortfolio())
		return false;

	UserSerialized obj = serializeUser();
	
	out.write((char *)&obj, sizeof(obj));
	out.close();

	return true;
}


bool User::deserialize() {
	ifstream in("save_u.cab", ios::binary);

	// File does not exist, first time user
	if(!in)
		return false;

	UserSerialized obj;
	in.read((char *)&obj, sizeof(obj));
	deserializeUser(obj);

	in.close();
	deserializePortfolio();

	return true;
}

bool User::deserializePortfolio() {
	ifstream in("save_p.cab", ios::binary);

	if(!in)
		return false;

	int n;
	in >> n;
	portfolio.reserve(n);

	for(int i = 0; i < n; i++) {
		Quote::QuoteSerialized obj;
		in.read((char *)&obj, sizeof(obj));

		Quote q(obj);
		portfolio.push_back(obj);
	}

	return true;
}

void User::deserializeUser(User::UserSerialized obj) {
	cashInHand = obj.cashInHand;
	totalWorth = obj.totalWorth;
	stockWorth = obj.stockWorth;
	name = obj.name;
}


// DEBUG CODE
User::User() {
	cashInHand = 10000.0f;
	stockWorth = 0.0f;
}

void User::buy(Quote q, int n) {
	q.refresh();
	double change = q.getnPrice() * n;

	cashInHand -= change;
	stockWorth += change;

	q.setNum(n);
	portfolio.push_back(q);
}

float User::sell(string s, int n) {
	int pos = getIndex(s);
	// Quote not in Portfolio. This should never happen
	if(pos == -1) return pos;

	Quote *q = &portfolio.at(pos);
	q->refresh();

	// Price to be sold at
	double price = q->getnPrice();
	int number = q->getNum();

	// Selling all the stocks
	if(number <= n) {
		portfolio.erase(portfolio.begin() + pos);
	} else {
		q->setNum(number - n);
	}

	double change = n * price;
	cashInHand += change;
	stockWorth -= change;

	return price;
}

Quote User::getQuote(int i) {
	return portfolio[i];
}

int User::getIndex(string s) {
	for(vector<Quote>::iterator i = portfolio.begin(); i != portfolio.end(); ++i)
		if(i->getSymbol() == s)
			return i - portfolio.begin();

	return -1;
}

vector<Quote> User::getPortfolio() { return portfolio; }

// Getters and setters
const char * User::getName()	{ return name.c_str(); }
double User::getStockWorth()	{ return stockWorth; }
double User::getCashInHand()	{ return cashInHand; }
double User::getTotalWorth()	{ return stockWorth + cashInHand; }

void User::setName(string n) {
	name = n;
}