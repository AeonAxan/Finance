#include <string>

#include "DownloadHandler.h"
#include "User.h"

#include <vector>

using namespace std;

DownloadHandler* DownloadHandler::mInstance = NULL;

int DownloadHandler::writer(char *mData, size_t mSize, size_t nmemb, void *ptr) {
	int res = 0;
	string *mBuffer = (string *) ptr;

	if(mBuffer != NULL) {
		res = mSize * nmemb;
		mBuffer->append(mData, res);
	}

	return res;
}

void DownloadHandler::initCURL() {
	curl = curl_easy_init();

	// Setup CURL options
	if(curl) {
		// URL SET LATER
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);	
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);	
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &DownloadHandler::writer);	
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &oBuffer);	
	}
}

// Constructor
DownloadHandler::DownloadHandler(string URL) {
	baseURL = URL;

	initCURL();
}


// PUBLIC FUNCTIONS
DownloadHandler * DownloadHandler::getDownloadHandler() {
	if(mInstance == NULL) {
		mInstance = new DownloadHandler("http://download.finance.yahoo.com/d/quotes.csv?s=%s&f=snl1d1t1c1&e=.csv");
	}

	return mInstance;
}

string DownloadHandler::download(const char *param) {
	// Must clear buffer everytime to avoid errors
	oBuffer = "";

	char URL[150];
	sprintf_s(URL, baseURL.c_str(), param);
	curl_easy_setopt(curl, CURLOPT_URL, URL);

	result = curl_easy_perform(curl);
	
	if(success())
		return oBuffer;
	else
		return "Error";
}

// Was the last download successful
bool DownloadHandler::success() {
	if(result == CURLE_OK)
		return true;
	else
		return false;
}

// Returns the error if last download was a failure
string DownloadHandler::getError() {
	if(!success())
		return errorBuffer;

	// Should not happen
	return "WRNOG CALL TO GETERROR";
}

// Check for internet connectivity
bool DownloadHandler::isConnected() {
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com/");

	result = curl_easy_perform(curl);
	
	return success();
}

// Destructor
DownloadHandler::~DownloadHandler() {
	curl_easy_cleanup(curl);
}


// Scores

void DownloadHandler::uploadScore(string username, double score) {
	char URL[150];
	sprintf(URL, "http://warhammer0.site50.net/finance.php?username=%s&score=%f", username.c_str(), score);

	curl_easy_setopt(curl, CURLOPT_URL, URL);

	curl_easy_perform(curl);
}

vector<DownloadHandler::Score> DownloadHandler::downloadScore() {
	oBuffer = "";

	curl_easy_setopt(curl, CURLOPT_URL, "http://warhammer0.site50.net/get.php");

	result = curl_easy_perform(curl);

	vector<Score> v;

	if(!success())
		return v;

	int x;
	string username;
	double score;

	while((x = oBuffer.find(',')) != string::npos) {
		Score s;
		username = oBuffer.substr(0, x);
		oBuffer.erase(0, x+1);

		x = oBuffer.find(',');
		score = atof(oBuffer.substr(0, x).c_str());
		oBuffer.erase(0, x+1);

		s.username = username;
		s.val = score;

		v.push_back(s);
	}

	return v;
}

