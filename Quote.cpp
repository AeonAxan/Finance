#include <string>

#include "Quote.h"
#include "DownloadHandler.h"

using std::string;

DownloadHandler* Quote::mDH = DownloadHandler::getDownloadHandler();

// Constructors

// should not be used !! testing
Quote::Quote() {}

Quote::Quote(string mSymbol, string mName, string mDate, string mTime, double mPrice, double mChange, int n) {
	symbol	= mSymbol;
	name	= mName;
	date	= mDate;
	time	= mTime;
	price	= mPrice;
	change	= mChange;
	number	= n;

	init = true;

}

Quote::Quote(string s, int n) {
	decode(s);
	number = n;
}

// Decodes Quote data from a CSV string
void Quote::decode(string s) {
	int x;

	// Symbol
	x = s.find(',');
	symbol = s.substr(1, x-2);
	s.erase(0, x+1);

	// Name
	x = s.find(',');
	name =  s.substr(1, x-2);
	s.erase(0, x+1);

	// Price
	x = s.find(',');
	price =  atof(s.substr(0, x).c_str());
	s.erase(0, x+1);

	// Date
	x = s.find(',');
	date =  s.substr(1, x-2);
	s.erase(0, x+1);

	// Time
	x = s.find(',');
	time =  s.substr(1, x-2);
	s.erase(0, x+1);

	// Change
	x = s.find(',');
	change =  atof(s.substr(0, x).c_str());
	s.erase(0, x+1);

	if(price == 0) {
		init = false;
		error = INVALID_SYMBOL;

	} else
		init = true;
}

// Convert current Quote object to a CSV format string
string Quote::encode() {
	if(!isInit())
		return "\"ERROR\",\"N/A\",0.00,\"N/A\",\"N/A\",N/A";

	char buffer[250];
	sprintf(buffer, "\"%s\",\"%s\",%g,\"%s\",\"%s\",%g", symbol.c_str(), name.c_str(), price, date.c_str(), time.c_str(), change);

	string out(buffer);
	return out;
}

Quote Quote::get(char *symbol, int n) {
	string res = mDH->download(symbol);

	if(mDH->success()) {
		Quote q(res, n);
		return q;
	}

	// In case of download Failure return empty object
	Quote q;
	q.error = CONNECTIVITY_ERROR;
	return q;
}

bool Quote::update() {
	string res = mDH->download(symbol.c_str());

	if(mDH->success()) {
		decode(res);
		return true;
	}

	// Update Failed
	return false;
}


string Quote::toString() {
	return encode();
}

string Quote::errorToString() {
	switch(error) {
	case INVALID_SYMBOL:
		return "Incorrect stock symbol";

	case CONNECTIVITY_ERROR:
		return "Internet connectivity error";

	default:
		return "No error occured";
	}
}

bool   Quote::isInit()				{ return init;				}
Quote::errorCode Quote::getError()	{ return error;				}

// Getters
string Quote::getSymbol()	{ return symbol;			}
string Quote::getName()		{ return name;				}
string Quote::getDateTime() { return date + " " + time; }
string Quote::getDate()		{ return date;				}
string Quote::getTime()		{ return time;				}
double Quote::getChange()	{ return change;			}
double Quote::getPrice()	{ return price;				}
int    Quote::getNum()      { return number;			}

int Quote::setNum(int n) {
	int tmp = number;
	number = n;
	return tmp;
}
