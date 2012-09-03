#include <string>

using std::string;

#include "User.h"
#include "DownloadHandler.h"

/*
 * Handles every user interaction with the console. Including the user input
 * This class has access to the global user object
 */
class ConsoleHandler {
public:
	enum menuSelection {
		BUY,
		SELL,
		PORTFOLIO,
		CONNECTIVITY,                              //changed from history to status
		EXIT,
		HIGH_SCORE
	};

private:
	bool connected;					// Keeps track of wheather we have an active internet connection

	// Utilities
	string space;
	void displayStats();
	bool isCinBad();

	User *user;

public:
	
	ConsoleHandler();				// initializes the class, also intializes the global User object

	void loading(char *);
	bool newUser();					// Displays the sign up form, sets the user name in the user object

	menuSelection mainMenu();		// Displays the main menu to the user, returns the enum of the selction
	void buyMenu();					// Displays the buy stock menu to the user
	void sellMenu();				// Displays the stock sell menu to the user
	void showPortfolio();			// Displays the portfolio of the user
	void showScores(DownloadHandler &);				// Displays the global scores

	void setConnectivity(bool);		// Sets the internet connectivity state
};

/* Notes
  
 * mainMenu() will return the menu item selected. It will not call the respective function like buyMenu()

 * Constructor should initialize the local copy of the user object. This will be required in buyMenu(), sellMenu() ...

 * buyMenu() will directly interface with the user class. similarly sell(), showPortfolio()..

 * User class's functions like buy or sell will not verify the input for number of stocks. So pass in verfied input only.

 */