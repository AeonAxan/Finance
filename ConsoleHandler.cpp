#include <iostream>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <limits>

// Disable min() max() macro defined by windows.h
#define NOMINMAX

#include "ConsoleHandler.h"
#include "user.h"
#include "DownloadHandler.h"

using namespace std;


// Constructor
ConsoleHandler::ConsoleHandler() { 
	user = User::getInstance();
	space = "       ";
}

//Not done Will define it later
bool ConsoleHandler::newUser() {
	system("cls");
	cout << "\n\n\n\n\n";
	cout << space << "Welcome to Stock Market v2.2!" << endl << endl;

	cout << space << "Ever wanted to try out your luck in the stock market, But dont have $10,000 to burn?" << endl;
	cout << endl << space << "If yes, Your are going to love this. We will give you $10k and let you buy any stocks  " << endl;
	cout << space << "you want for real time prices. You get to trade your stocks and make profit. or loss" << endl << endl;

	cout << space << "Lets get started ?, type 'y' or 'n'" << endl << endl;
	cout << space << "> ";
	
	char ch;
	cin >> ch;

	if(isCinBad()) {
		system("cls");
		cout << "\n\n\n\n\n";
		cout << space << "Uncool!" << endl << endl;
		getch();
		return false;
	}

	if(ch == 'n') {
		cout << endl << endl;
		cout << space << "Well you were lame anyway!" << endl << endl;
		getch();
		return false;
	
	} else if(ch == 'y') {
		string name;

		cout << endl << endl;
		cout << space << "You are awesome!" << endl;
		cout << space << "Type your name to get started : ";

		cin >> name;
		user->setName(name);
		return true;
	
	} else {
		string name;

		cout << endl << endl;
		cout << space << "Well either you cant type or read. But we will take what we get." << endl;
		cout << space << "Type your name to get started (please do better this time) : ";

		cin >> name;
		user->setName(name);
		return true;
	}
}


ConsoleHandler::menuSelection ConsoleHandler::mainMenu()
{
	int  ch;
	int flag = 0;
	int width = 43;

	while(1)
	{
		// set custom space value
		space = "             ";

		system("cls");
		cout << "\n\n\n\n\n";
		cout << space << space << "--------------------------------------------" << endl;
		cout << space << space << setw(width) << left << "|            Stock Market v2.2" << setw(1) << "|" << endl;
		cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;

		if(!connected) {
			cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;
			cout << space << space << setw(width) << left << "|   * - Requires internet connection " << setw(1) << "|" << endl;
			cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;
			cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;
			cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;
		}

		//checks internet connectivity in main menu
		if(connected)
			cout << space << space << setw(width) << left << "|   1. Buy Stocks" << setw(1) << "|" << endl;
		else
			cout << space << space << setw(width) << left << "|   *. Buy Stocks" << setw(1) << "|" << endl;

		cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;
	 
		if(connected)
			cout << space << space << setw(width) << left << "|   2. Sell Stocks" << setw(1) << "|" << endl;
		else
			cout << space << space << setw(width) << left << "|   *. Sell Stocks" << setw(1) << "|" << endl;
	 
		cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;
		cout << space << space << setw(width) << left << "|   3. View Portfolio" << setw(1) << "|" << endl;
		cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;  
		
		if(connected)
			cout << space << space << setw(width) << left << "|   4. View Global Highscores" << setw(1) << "|" << endl;
		else
			cout << space << space << setw(width) << left << "|   *. View Global Highscores" << setw(1) << "|" << endl;

		cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;  
		cout << space << space << setw(width) << left << "|   5. Save and Exit" << setw(1) << "|" << endl;
		cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;
		cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;

		if(!connected)
			cout << space << space << setw(width) << left << "|   6. Recheck Internet Connection" << setw(1) << "|" << endl;

		cout << space << space << setw(width) << "|" << setw(1) << "|" << endl;
		cout << space << space << "--------------------------------------------" << endl << endl;
	
		if(flag == 1)
			cout << space << space << "    " << "* Incorrect Choice!" << endl;
			
		else if(flag == 2)
			cout << space << space << "    " << "* Cannot Use this option without an internet connection!" << endl;
			
		cout << endl << space << space << "    " << "Enter your choice" << endl << endl;
		cout << space << space << "    " << "> ";
		cin >> ch;
		  
		if(isCinBad()) {
			ch = 9;
		}
		
		// Reset space value to default
		space = "       ";

		switch(ch) {
		case 1: 
			if(connected)
				return(BUY);
			else 
				flag=2;
			break;

		case 2: 
			if(connected)
				return(SELL);
			else
				flag=2;
			break;

		case 3: 
			return(PORTFOLIO);
			break;

		case 4:
			if(connected)
				return HIGH_SCORE;
			else
				flag = 2;
			break;

		case 6: 
			if(!connected)
				return(CONNECTIVITY);
			break;

		case 5:
			return(EXIT);
			break; 
		
		default:
			flag=1;	
		}	   
	}
}

void ConsoleHandler::buyMenu() {
	enum errors { CLEAN, WRONG_SYMBOL, INSUFF_FUNDS, WRONG_VALUE};

	errors e = CLEAN;
	string symbol;

	double change;
	int possibleBuy, n, ch;

	while(1) {
		system("cls");
		cout << "\n\n\n\n";
		cout << space << space << space << "Sell Stock. Enter the serial number, 'b' to go back.\n\n";

		if(e == WRONG_SYMBOL)
			cout << space << space << space << "We could not find that stock in the market." << endl << endl;
		else if(e == INSUFF_FUNDS)
			cout << space << space << space << "Insufficient funds to buy that stock" << endl << endl;
		else if(e == WRONG_VALUE)
			cout << space << space << space << "Incorrect value of n" << endl << endl;

		cout << space << space << space << "Stock Symbol : ";
		cin >> symbol;

		// Go Back
		if(symbol == "b")
			return;
		
		Quote q = Quote::get(symbol.c_str());
		if(!q.isInit()) {
			e = WRONG_SYMBOL;
			continue;
		}

		possibleBuy = (int)(user->getCashInHand()/q.getoPrice());
		if(possibleBuy == 0) {
			e = INSUFF_FUNDS;
			continue;
		}

		cout << endl << endl;

		cout << space << space << space << space << setw(15) << right << "Price : " << q.getoPrice() << endl;
		cout << space << space << space << space << setw(15) << right << "Name : " << q.getName() << endl;
		cout << space << space << space << space << setw(15) << right << "Change : " << q.getoChange() << endl;
		cout << space << space << space << space << setw(15) << right << "DateTime : " << q.getoDateTime()<< endl;

		possibleBuy = (int)(user->getCashInHand()/q.getoPrice());

		cout << endl << endl;
		cout << space << space << space << "You can buy " << possibleBuy << " shares of " << q.getSymbol() << endl;
		cout << space << space << space << "How many do you want to buy. 'c' to cancel transaction" << endl << endl;
		cout << space << space << space << "> ";
		cin >> n;

		// Cancel
		if(isCinBad()) {
			e = CLEAN;
			continue;
		}

		if(n <= 0 || n > possibleBuy) {
			e = WRONG_VALUE;
			continue;
		}

		change = n * q.getoPrice();

		// Header
		int A = 24, B = 6;
		cout << endl << endl << space << space << setw(A) << left << "Before" << setw(A) << "          | After" << endl;
		cout << space << space << "-------------------------------------------------------------------------" << endl << endl;

		cout << left << fixed << setprecision(2);
		cout << space << space << setw(A) << "Cash In Hand : " << setw(B) << user->getCashInHand() << setw(1) << "   |";
		cout << space << setw(A) << "Cash In Hand : " << setw(B) << user->getCashInHand() - change << endl;

		cout << space << space << setw(A) << "Stocks Worth : " << setw(B) << user->getCashInHand() << setw(1) << "   |";
		cout << space << setw(A) << "Stocks Worth : " << setw(B) << user->getCashInHand() + change << endl;

		cout << endl;
		cout << space << space << setw(A) << "Total Assets : " << setw(B) << user->getCashInHand() << setw(1) << "   |";
		cout << space << setw(A) << "Total Assets : " << setw(B) << user->getCashInHand() << endl;

		// Confirmation
		cout << endl << endl;
		cout << space << space << "1 to Confirm, 'c' to cancel" << endl << endl;
		cout << space << space << "> ";
		cin >> ch;

		if(isCinBad() || ch != 1) {
			e = CLEAN;
			continue;
		}

		// Confirmed
		system("cls");
		cout << "\n\n\n\n";
		cout << space << space << space << "Contacting Stock Exchange servers.." << endl << endl;
		user->buy(q, n);

		cout << space << space << space << "Transaction Successful!" << endl;
		cout << space << space << space << "You are now the owner of " << n << " new " << q.getSymbol() << " shares.";

		cout << endl << endl;
		cout << space << space << space << "Press any key to continue . . .";
		getch();
		e = CLEAN;
	}
}

void ConsoleHandler::sellMenu() {
	bool error = false;

	while(1) {
		system("cls");

		cout << "\n\n\n\n";
		cout << space << "Sell Stock. Enter the serial number, 'b' to go back.\n\n";

		// Table Header 7 spaces left
		cout <<  space << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
		cout << left << endl << "       ";
		cout << setw(10) << "+ Symbol";
		cout << setw(25) << "+ Name";
		cout << setw(10)  << "+ Price";
		cout << setw(11) << "+ Number";
		cout << setw(10) << "+ Change";
		cout << setw(20) << "+ Datetime" << "+";
		cout << endl;
		cout <<  space << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	
		cout << left << space;
		cout << setw(10) << "|       ";
		cout << setw(25) << "|     ";
		cout << setw(10)  << "|      ";
		cout << setw(11) << "|      ";
		cout << setw(10) << "|      ";
		cout << setw(20) << "|       " << "|";
		cout << endl;


		// Table contents
		vector<Quote> p = user->getPortfolio();
		int j = 1;
		for(vector<Quote>::iterator i = p.begin(); i  != p.end(); ++i, ++j) {
			cout << "      " << j << left;
			cout << "| " << setw(8) << i->getSymbol();
			cout << "| " << setw(23) << i->getName();
			cout << "| " << setw(8) << i->getoPrice();
			cout << "| " << setw(9) << i->getNum();
			cout << "| " << setw(8) << i->getoChange();
			cout << "| " << setw(18) << i->getoDateTime() << "|";
			cout << endl;
		}

		cout << left << space;
		cout << setw(10) << "|       ";
		cout << setw(25) << "|     ";
		cout << setw(10)  << "|      ";
		cout << setw(11) << "|      ";
		cout << setw(10) << "|      ";
		cout << setw(20) << "|       " << "|";
		cout << endl;

		cout << space << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

		cout << endl << endl;

		if(error) {
			cout << space << space << "Incorrect choice!" << endl << endl;
		}

		int choice;
		cout << space << space << "Serial Number : ";
		cin >> choice;

		// Character was entered;
		if(isCinBad())
			return;

		if(choice > p.size() || choice <= 0) {
			error = true;
			continue;
		}

		Quote q = p.at(choice - 1);

		int n;
		cout << endl << space << space << "Number of stocks to be sold : ";
		cin >> n;

		if(isCinBad()) {
			error = true;
			continue;
		}

		if(n > q.getNum() || n <= 0) {
			error = true;
			continue;
		}

		error = false;

		system("cls");

		cout << endl << endl << space << space;
		cout << "Querying stock market for prospective buyers.." << endl << endl;

		double soldAt;
		double price = q.getoPrice();
		soldAt = user->sell(q.getSymbol(), n);
	
		cout << endl << space << space;
		cout << n << " Stocks of " << q.getName() << " sold for " << soldAt << " each." << endl;
		cout << space << space;

		double profit = (soldAt * n) - (price * n);
		cout << "You have made a profit of : [ " << fixed << setprecision(2) << profit << " ]" << endl << endl << endl;

		cout << endl << endl;
		displayStats();
		cout << endl << endl << space << space << "Press any key to continue . . . ";
		getch();
	}

	getch();
}

void ConsoleHandler::loading(char *s) {
	system("cls");
	cout << endl << endl << endl;
	cout <<  space << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << endl << endl;
	cout << space << "+" << space << s << endl;
	cout << endl << endl;
	cout <<  space << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void ConsoleHandler::setConnectivity(bool b) {
	cout << "Set Connectivity : " << b << endl;
	connected = b;

}

void ConsoleHandler::showPortfolio() {
	system("cls");

	cout << "\n\n\n\n\n";

	// Table Header 7 spaces left
	cout <<  space << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
	cout << left << endl << "       ";
	cout << setw(10) << "+ Symbol";
	cout << setw(25) << "+ Name";
	cout << setw(10)  << "+ Price";
	cout << setw(11) << "+ Number";
	cout << setw(10) << "+ Change";
	cout << setw(20) << "+ Datetime" << "+";
	cout << endl;
	cout <<  space << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	
	cout << left << space;
	cout << setw(10) << "|       ";
	cout << setw(25) << "|     ";
	cout << setw(10)  << "|      ";
	cout << setw(11) << "|      ";
	cout << setw(10) << "|      ";
	cout << setw(20) << "|       " << "|";
	cout << endl;


	// Table contents
	vector<Quote> p = user->getPortfolio();
	for(vector<Quote>::iterator i = p.begin(); i  != p.end(); ++i) {
		cout << "       " << left;
		cout << "| " << setw(8) << i->getSymbol();
		cout << "| " << setw(23) << i->getName();
		cout << "| " << setw(8) << i->getoPrice();
		cout << "| " << setw(9) << i->getNum();
		cout << "| " << setw(8) << i->getoChange();
		cout << "| " << setw(18) << i->getoDateTime() << "|";
		cout << endl;
	}

	cout << left << space;
	cout << setw(10) << "|       ";
	cout << setw(25) << "|     ";
	cout << setw(10)  << "|      ";
	cout << setw(11) << "|      ";
	cout << setw(10) << "|      ";
	cout << setw(20) << "|       " << "|";
	cout << endl;

	cout << space << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	cout << endl << endl << endl;

	displayStats();
	
	cout << endl << endl << space << "Press any key to continue . . . ";
	getch();
}


void ConsoleHandler::showScores(DownloadHandler &mDH) {
	
	loading("Fetching Scores from our server . . .");
	vector<DownloadHandler::Score> s = mDH.downloadScore();
	
	system("cls");	
	cout << "\n\n\n\n\n";

	int width = 20;

	// Header
	cout << space << space << "---------------------------------------------" << endl;
	cout << space << space << setw(width) << "|" << setw(1) << "|" << setw(width) << " " << setw(1) << "   |" << endl;
	cout << space << space << setw(width) << left << "| Name" << setw(1) << "|";
	cout << setw(width) << left << "  Score" << setw(1) << "   |" << endl;
	cout << space << space << setw(width) << "|" << setw(1) << "|" << setw(width) << " " << setw(1) << "   |" << endl;
	cout << space << space << "---------------------------------------------" << endl;
	cout << space << space << setw(width) << "|" << setw(1) << "|" << setw(width) << " " << setw(1) << "   |" << endl;
	
	if(s.size() == 0) {
		system("cls");	
		cout << "\n\n\n\n\n";
		cout << space << space << space << "Unfortunately we have encountered an error";
		cout << endl << space << space << space << "Please try again later";

		cout << endl << space << space << space << "Press any key to go back . . .";
		getch();
		return;
	}

	for(vector<DownloadHandler::Score>::iterator i = s.begin(); i != s.end(); ++i) {
		cout << space << space <<  left << "| " << setw(width-3)  << i->username << setw(1) << " |  ";
		cout << setw(width) << left << i->val << setw(1) << " |" << endl;
	}

	cout << space << space << setw(width) << "|" << setw(1) << "|" << setw(width) << " " << setw(1) << "   |" << endl;
	cout << space << space << "---------------------------------------------" << endl;

	cout << endl << endl;
	cout << space << space << "Press any key to go back . . .";
	getch();
}


// Utility functions
void ConsoleHandler::displayStats() {
	cout << right << fixed << setprecision(2);
	cout << space << setw(25) << "Cash In Hand : " << setw(10) << user->getCashInHand() << endl;
	cout << space << setw(25) << "Stocks Worth : " << setw(10) <<user->getStockWorth() << endl;
	cout << endl;
	cout << space << setw(25) << "Total Worth : " << setw(10) <<user->getTotalWorth() << endl;
}

bool ConsoleHandler::isCinBad() {
	if(cin.fail()) {
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return true;
		}

	return false;
}