#pragma once
#include <iostream>

#include "MainClass.h"

class CSchwabApiData
{
private:
	string AppKey;
	string Secret;
	string callbackURL;
public:
	void setAppKey();
	void setSecret();
	void setCallbackUrl();
	string getAppKey();
	string getSecret();
	string getCallbackUrl();
};

