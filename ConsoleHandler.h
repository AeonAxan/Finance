#include <string>

using std::string;

#include "User.h"
#include "DownloadHandler.h"

class ConsoleHandler {
public:
	enum menuSelection {
		BUY, SELL, PORTFOLIO, CONNECTIVITY,                          
		EXIT, HIGH_SCORE
	};

private:
	bool connected;
	User *user;

	// Utilities
	string space;
	void displayStats();
	bool isCinBad();

public:
	// initializes the class, also intializes the global User object
	ConsoleHandler();				

	void loading(char *);
	// Displays the sign up form, sets the user name in the user object
	bool newUser();					

	// Displays the main menu to the user, returns the enum of the selction
	menuSelection mainMenu();		
	// Displays the buy stock menu to the user
	void buyMenu();					
	// Displays the stock sell menu to the user
	void sellMenu();				
	// Displays the portfolio of the user
	void showPortfolio();			
	// Displays the global scores
	void showScores(DownloadHandler &);				

	// Sets the internet connectivity state
	void setConnectivity(bool);		
};