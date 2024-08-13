#include "SchwabApiData.h"

void CSchwabApiData::setAppKey()
{
	this->AppKey = "SxKAAPt0keojyrqk6siWVtMvHxN1ZgfL";
}

void CSchwabApiData::setSecret()
{
	this->Secret = "1Fr6OgR9ilAkFBpK";
}

void CSchwabApiData::setCallbackUrl()
{
	this->callbackURL = "https://client.schwab.com/Areas/Access/Login";
}

string CSchwabApiData::getAppKey()
{
	return this->AppKey;
}

string CSchwabApiData::getSecret()
{
	return this->Secret;
}

string CSchwabApiData::getCallbackUrl()
{
	return this->callbackURL;
}
