#ifndef _DHANDLER
#define _DHANDLER

#include <string>
#include <vector>
#include <curl/curl.h>

using std::string;
using std::vector;

/*
 * A simple wrapper for libcurl
 * returns the data downloaded as a std::string

 * Note : This is a singleton class. It cannot be instantiated. Call the factory method
 *        getDownloadHandler() to get an instance of the downloadManager.
 */
class DownloadHandler {
private:
	static DownloadHandler *mInstance;		// The unique instance

	DownloadHandler(string);				// Constructor, @param = base URL

	string baseURL;							// Base Download URL, passed in the Constructor
	string oBuffer;							// Buffer used to write the downloaded data to
	
	char errorBuffer[CURL_ERROR_SIZE];		// Curl Error Buffer
	CURL *curl;								// Working instance of CURL
	CURLcode result;						// Return result code of last executed curl request
	
	void initCURL();						// Initiates all the curl settings
		
	// CURLOPT_WRITEFUNCTION
	// Note : Static for compatibility, since curl was designed for C. not C++
	static int writer(char *, size_t, size_t, void *);
	
public:
	struct Score {
		string username;
		double val;
	};

	static DownloadHandler* getDownloadHandler();

	bool success();							// Was the last executed curl request a success
	string getError();						// If applicable, the error desc of the last executed request

	/*
	 * The main Download Method, Takes in the Quote name and returns
	 * the downloaded data as a string. 
	 */
	string download(const char *);

	// Scores
	void uploadScore(string, double);
	vector<DownloadHandler::Score> downloadScore();


	bool isConnected();						// Check if we have a working internet connection

	~DownloadHandler();						// Cleans up curl
};

#endif
