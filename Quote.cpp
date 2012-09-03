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
	odate	= mDate;
	otime	= mTime;
	oprice	= mPrice;
	ochange	= mChange;
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
	oprice =  atof(s.substr(0, x).c_str());
	s.erase(0, x+1);

	// Date
	x = s.find(',');
	odate =  s.substr(1, x-2);
	s.erase(0, x+1);

	// Time
	x = s.find(',');
	otime =  s.substr(1, x-2);
	s.erase(0, x+1);

	// Change
	x = s.find(',');
	ochange =  atof(s.substr(0, x).c_str());
	s.erase(0, x+1);

	if(oprice == 0) {
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
	sprintf(buffer, "\"%s\",\"%s\",%g,\"%s\",\"%s\",%g", symbol.c_str(), name.c_str(), oprice, odate.c_str(), otime.c_str(), ochange);

	string out(buffer);
	return out;
}

Quote Quote::get(const char *symbol, int n) {
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

void Quote::updateOriginals() {
	odate	= ndate;
	otime	= ntime;
	oprice	= nprice;
	ochange	= nchange;
}

bool Quote::refresh() {
	string res = mDH->download(symbol.c_str());

	if(mDH->success()) {
		update(res);
		return true;
	}

	// Update Failed
	return false;
}

// Updates the ndata using the csv string. Does not touch the original data
void Quote::update(string s) {
	int x;

	// Symbol
	x = s.find(',');
	s.erase(0, x+1);

	// Name
	x = s.find(',');
	s.erase(0, x+1);

	// Price
	x = s.find(',');
	nprice =  atof(s.substr(0, x).c_str());
	s.erase(0, x+1);

	// Date
	x = s.find(',');
	ndate =  s.substr(1, x-2);
	s.erase(0, x+1);

	// Time
	x = s.find(',');
	ntime =  s.substr(1, x-2);
	s.erase(0, x+1);

	// Change
	x = s.find(',');
	nchange =  atof(s.substr(0, x).c_str());
	s.erase(0, x+1);
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


// Serialization/Deserialization
Quote::QuoteSerialized Quote::serialize() {
	QuoteSerialized obj;

	strcpy(obj.name, name.c_str());
	strcpy(obj.date, odate.c_str());
	strcpy(obj.symbol, symbol.c_str());
	strcpy(obj.time, otime.c_str());
	obj.change = ochange;
	obj.number = number;
	obj.price = oprice;
	
	return obj;
}

Quote::Quote(Quote::QuoteSerialized obj) {
	name = obj.name;
	odate = obj.date;
	symbol = obj.symbol;
	otime = obj.time;
	ochange = obj.change;
	number = obj.number;
	oprice = obj.price;

	init = true;
}


bool   Quote::isInit()				{ return init;}
Quote::errorCode Quote::getError()	{ return error;	}

// Getters
string Quote::getSymbol()	{ return symbol; }
string Quote::getName()		{ return name; }

string Quote::getoDateTime() { return odate + " " + otime; }
string Quote::getoDate()		{ return odate;	}
string Quote::getoTime()		{ return otime;	}
double Quote::getoChange()	{ return ochange; }
double Quote::getoPrice()	{ return oprice; }

string Quote::getnDateTime() { return ndate + " " + ntime; }
string Quote::getnDate()		{ return ndate;	}
string Quote::getnTime()		{ return ntime;	}
double Quote::getnChange()	{ return nchange; }
double Quote::getnPrice()	{ return nprice; }

int    Quote::getNum()      { return number; }

int Quote::setNum(int n) {
	int tmp = number;
	number = n;
	return tmp;
}
