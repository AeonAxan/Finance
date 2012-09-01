#ifndef _USER
#define _USER

#include <string>
#include <vector>

#include "Quote.h"

using std::string;
using std::vector;

/*
 * Keeps track of all the details of the current User
 */
class User {
	// Singleton methods
	static User *mInstance;				// The instance of the user object to be used
	User() {};							// Private constructor, singleton class

	vector<Quote> portfolio;			// Keeps Track of all the Quotes the user owns
	double cInHand;						// Cash the user has in hand

	string name;
	double stockWorth, totalWorth;

	string failError;					// Last thrown error by the class

public:
	
	static User * getInstance();

	// Buys n of the given Quote; Will return false if :
	//		Not enough cash
	//		Quote invalid
	bool buy(Quote, int);	

	// Sells n of the given Quote; Will return false if :
	//		Quote not in portfolio
	//		n number of Quote not in portfolio
	//		Quote invalid
	bool sell(Quote, int);				


	// Utility Functinos
	bool hasQuote(Quote);
	Quote getQuote(string);


	// Getters and setters
	char * getName();
	double getStockWorth();
	double getCashInHand();
	double getTotalWorth();

	void setName(char *);
	
	string getError();

};

#endif
