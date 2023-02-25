#ifndef APICALLER
#define APICALLER

#include "Base.h"
#include "WiFiManager.h"
#include <HTTPClient.h>

struct ApiCredentials {
  String name;
  String apiKey;
  String apiKeyLabel;
  String apiUrl;
};

class ApiCaller : public Base {
  public:
    ApiCaller(ApiCredentials apiCredentials, WifiManager wifiManager) {
      this->apiCredentials = apiCredentials;

      // Connect to the Wi-Fi network
      wifiManager.connect();

      // Initialize the HTTP client
      httpClient.begin(wifiClient, apiCredentials.apiUrl);

      printCreateMessage();
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
        response = http.getString();
        println("Current BTC/EUR price: ");
        print(response);
      } else {
        println("Error getting price information. Status code: ");
        print(String(httpCode));
        response = http.getString();
        println(response);
      }

      http.end();
      return response;
    }

    private:
      ApiCredentials apiCredentials;
      WiFiClient wifiClient;
      HTTPClient httpClient;
  
      const String toString() override {
        return "ApiCaller.h";
      }
};

#endif // BASE
