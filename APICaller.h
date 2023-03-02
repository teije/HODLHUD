#ifndef APICALLER
#define APICALLER

#include "Base.h"
#include "WifiManager.h"
#include <HTTPClient.h>

struct ApiCredentials {
  String name;
  String apiKey;
  String apiKeyLabel;
  String apiUrl;
};

class ApiCaller : public Base {
  public:
    ApiCaller(ApiCredentials apiCredentials, WifiManager wifiManager): wifiManager(wifiManager) {
      this->apiCredentials = apiCredentials;
      
      // Initialize the HTTP client
      httpClient.begin(wifiClient, apiCredentials.apiUrl);

      printCreateMessage();
    }

    String GET(String endpoint) {
      // Ensure that there is a wifi connection
      wifiManager.ensureConnection();
      
      HTTPClient http;
      String url = apiCredentials.apiUrl + endpoint;
      http.begin(url);
      http.addHeader(apiCredentials.apiKeyLabel, apiCredentials.apiKey);

      int httpCode = http.GET();
      println("Executing GET request on: " + url);
      String response = "";
      if (httpCode == HTTP_CODE_OK) {
        response = http.getString();
        println("Response code: ");
        print(String(httpCode));
        println("Response message: ");
        print(response);
      } else {
        println("Error in response. Status code: ");
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
    WifiManager wifiManager;
    HTTPClient httpClient;

    const String type() override {
      return "ApiCaller.h";
    }
};

#endif // BASE
