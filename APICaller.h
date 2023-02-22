#include "Base.h"
#include <HTTPClient.h>

#ifndef APICALLER
#define APICALLER
struct ApiCredentials {
  String name;
  String apiKey;
  String apiKeyLabel;
  String apiUrl;
};

class ApiCaller : public Base {
  private:
    ApiCredentials apiCredentials;
    WiFiClient wifiClient;
    HTTPClient httpClient;

    const String toString() override {
      return "ApiCaller.h";
    }

  public:
    ApiCaller(ApiCredentials apiCredentials, WifiManager wifiManager) {
      this->apiCredentials = apiCredentials;

      // Connect to the Wi-Fi network
      wifiManager.connect();

      // Initialize the HTTP client
      httpClient.begin(wifiClient, apiCredentials.apiUrl);
    }

    String GET(String endpoint) {
      HTTPClient http;
      String url = apiCredentials.apiUrl + endpoint;
      http.begin(url);
      http.addHeader(apiCredentials.apiKeyLabel, apiCredentials.apiKey);

      int httpCode = http.GET();
      println("Executing GET request on: " + url);
      String response = "";
      if (httpCode == HTTP_CODE_OK) {
        String response = http.getString();
        println("Current BTC/EUR price: ");
        print(response);
      } else {
        println("Error getting price information. Status code: ");
        print(String(httpCode));
        String response = http.getString();
        println(response);
      }

      http.end();
      return response;
    }
};

#endif // BASE
