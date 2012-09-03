#include "ConsoleHandler.h"
#include "User.h"

using namespace std;

int main() {
	User *mUser = User::getInstance();
	DownloadHandler *mDH = DownloadHandler::getDownloadHandler();
	ConsoleHandler mCH;
	
	// Display Loading message because isConnected will take some time
	mCH.loading("Contacting Stock Exchange...");

	bool connected = mDH->isConnected();
	mCH.setConnectivity(connected);

	mCH.loading("Starting our Game Engine...");
	mDH->isConnected();
	// New User
	if(!mUser->deserialize())
		if(!mCH.newUser())
			return 0;

	while(1) {
		// Display main menu
		ConsoleHandler::menuSelection selection = mCH.mainMenu();

		switch(selection) {
	
		case ConsoleHandler::BUY :
			mCH.buyMenu();
			break;

		case ConsoleHandler::SELL :
			mCH.sellMenu();
			break;
	
		case ConsoleHandler::PORTFOLIO :
			mCH.showPortfolio();
			break;

		case ConsoleHandler::HIGH_SCORE :
			mCH.showScores(*mDH);
			break;

		case ConsoleHandler::CONNECTIVITY :
			mCH.loading("Checking your internet connection..");

			connected = mDH->isConnected();
			mCH.setConnectivity(connected);
			break;

		case ConsoleHandler::EXIT :
			mCH.loading("Saving all your hanrd earned money...");
			// Save User state
			mUser->serialize();

			mCH.loading("Uploading your score to our server...");
			mDH->uploadScore(mUser->getName(), mUser->getTotalWorth());
			return 0;
		}
	}
}