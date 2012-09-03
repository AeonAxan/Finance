#ifndef _QUOTE
#define _QUOTE

#include <string>

#include "DownloadHandler.h"

using std::string;

/*
 * The Quote Object. holds the data for a stock
 */
class Quote {
public:
	// Error Codes
	enum errorCode {
		INVALID_SYMBOL,
		CONNECTIVITY_ERROR
	};

	struct QuoteSerialized {
		char symbol[25], name[50], date[25], time[25];
		double change, price;
		int number;
	};

private:
	Quote();									// Cannot be instantiated without parameters

	// Private data variables
	string symbol, name;

	// Original Data
	string odate, otime;
	double ochange, oprice;

	// New Data
	string ndate, ntime;
	double nchange, nprice;

	int number;

	bool init;					
	errorCode error;

	static DownloadHandler *mDH;				// The instance of the singleton Downloadhandler

	void decode(string);						// Populates the data variables with the given csv string
	string encode();							// Converts the current data variables to a csv string
	void update(string);						// Updates ndata using the downloaded csv string

public:

	Quote(string, int n = 1);												// Build From csv string, second param = num
	Quote(string, string, string, string, double, double, int n = 1);		// Build from values

	static Quote get(const char *, int n = 1);		// Quote Factory. Creates a Quote object from the given symbol

	void updateOriginals();						// Copies all the values in n data to o data. Refresh should have been called before
	bool refresh();								// Downloads updated data, original data kept intact
	string toString();							// returns a csv string representation of the object

	bool isInit();								// Is the Quote object's data members populated properly
	errorCode getError();						// Returns the enum constant of the error
	string errorToString();						// Returns the latest error as a string
	
	// Class Serialization
	QuoteSerialized serialize();				// Returns a serialized struct of the class which can be saved to a file
	Quote(QuoteSerialized);						// Builds a quote object from the serialized struct

	// Getters
	string getSymbol();
	string getName();

	string getoDateTime();
	string getoDate();
	string getoTime();
	double getoChange();
	double getoPrice();

	string getnDateTime();						// Never call any get n function without refreshing it first. 
	string getnDate();
	string getnTime();
	double getnChange();
	double getnPrice();

	int getNum();

	int setNum(int);							// Returns the previous number value
};


#endif