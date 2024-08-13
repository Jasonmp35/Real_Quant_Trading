#include "MainDriver.h"
#include "MainClass.h"
#include "SchwabApiData.h"
#include "Schwab.h"
#include "future"

int main() {
    
    // Start the program
    std::cout << "Program started." << std::endl;
    
    CSchwabApiData data;
    CSchwab API;
    CMainClass driver;
    
    data.setAppKey();
    data.setSecret();
    data.setCallbackUrl();

    string appKey = data.getAppKey();
    string secret = data.getSecret();
    string callBack = data.getCallbackUrl();

    std::string auth_url = "https://api.schwabapi.com/v1/oauth/authorize?client_id=" + appKey+ "&redirect_uri=" + API.url_encode(callBack);
    std::cout << "Navigate to the following URL to authorize the app:\n" << auth_url << std::endl;

    // Step 2: Manually handle redirect and get the authorization code
    std::string authCode;
    std::cout << "Enter the authorization code: ";
    std::cin >> authCode;

    string accessToken = API.exchangeAuthCodeForToken(authCode, appKey, secret, callBack);
    API.makeAuthenticatedRequest(accessToken);

    return 0;
}