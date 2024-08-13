#pragma once
#include <iostream>
#include <iostream>
#include <mutex>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <thread>
#include <string>
#include <exception>

#include <curl/curl.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <cpprest/filestream.h>

using namespace std;

class CSchwab
{
public:
	string url_encode(const std::string& value);
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	string exchangeAuthCodeForToken(const std::string& authCode, const std::string& client_id, const std::string& client_secret, const std::string& redirect_uri);
	void makeAuthenticatedRequest(const std::string& accessToken);
private:

};

