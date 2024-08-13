#include "Schwab.h"
#include "SchwabApiData.h"


// Utility function to encode URL parameters
string CSchwab::url_encode(const string& value) {
    CURL* curl = curl_easy_init();
    char* output = curl_easy_escape(curl, value.c_str(), value.length());
    std::string encoded(output);
    curl_free(output);
    curl_easy_cleanup(curl);
    return encoded;
}

// Function to handle the response data from libcurl
size_t CSchwab::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to exchange authorization code for access token
string CSchwab::exchangeAuthCodeForToken(const std::string& authCode, const std::string& client_id, const std::string& client_secret, const std::string& redirect_uri) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.schwabapi.com/v1/oauth/token");
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        std::string postFields = "grant_type=authorization_code&code=" + authCode + "&redirect_uri=" + url_encode(redirect_uri) + "&client_id=" + client_id + "&client_secret=" + client_secret;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return readBuffer;
}

// Function to make authenticated API request using cpprestsdk
void CSchwab::makeAuthenticatedRequest(const std::string& accessToken)
{
    web::http::client::http_client client(U("https://api.schwab.com/v1/oauth/token"));
    web::http::http_request request(web::http::methods::GET);

    utility::string_t bearerToken = U("Bearer ") + utility::conversions::to_string_t(accessToken);

    request.headers().add(U("Authorization"), bearerToken);

    client.request(request).then([](web::http::http_response response) {
        if (response.status_code() == web::http::status_codes::OK) {
            auto body = response.extract_json().get();
            std::wcout << body.serialize() << std::endl;
        }
        else {
            std::wcerr << "Error: " << response.status_code() << std::endl;
        }
        }).wait();
}