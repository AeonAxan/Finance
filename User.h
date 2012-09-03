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
private:
	// Serializable User class struct
	struct UserSerialized {
		double cashInHand, stockWorth, totalWorth;
		char name[250];
	};

	// Singleton methods
	static User *mInstance;				// The instance of the user object to be used
	User();								// Private constructor, singleton class

	vector<Quote> portfolio;			// Keeps Track of all the Quotes the user owns

	string name;
	double stockWorth, totalWorth, cashInHand;

	// Serialization/Deserialization functions
	bool serializePortfolio();
	bool deserializePortfolio();

	UserSerialized serializeUser();
	void deserializeUser(UserSerialized);

public:
	
	static User * getInstance();

	// Deserializing/Serializing the User class

	// deserialize will return false if the user is using the app for the first time
	bool deserialize();
	bool serialize();


	// IMPORTANT : All Error checking should be done before calling sell() or buy(). 

	// Buys n of the given Quote. 
	// Expect a lag
	void buy(Quote, int);	

	// Will return a float with the price it was sold for
	// the sold stock (included price sold at)
	// Takes in two params, the name of stock and number to sell
	float sell(string, int);				


	// Utility Functinos
	int getIndex(string);					// Returns the index of the Quote object in the portfolio
											// IMPORTANT : Make sure it is not -1, which means not found

	Quote getQuote(int);					// Returns the Quote at the corrosponding portfolio position
											// MUST be a valid index

	vector<Quote> getPortfolio();			// Returns a vector of all the Quotes in the portfolio

	// Getters and setters
	const char * getName();
	double getStockWorth();
	double getCashInHand();
	double getTotalWorth();

	void setName(string);
	
	string getError();

};

#endif
