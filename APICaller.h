#ifndef APICALLER
#define APICALLER

#include "Base.h"
#include "WifiManager.h"
#include <HTTPClient.h>

class ApiCaller : public Base {
  public:
    ApiCredentials apiCredentials;  // Credentials to specific what url & key to use
    HTTPClient httpClient;          // Client to execute the calls to the api
    WiFiClient wifiClient;          // Client to store a wifi connection
    WiFiManager wifiManager;        // Manager to establish a wifi connection

    ApiCaller(ApiCredentials apiCredentials, WiFiManager wifiManager): wifiManager(wifiManager) 
    {
      this->apiCredentials = apiCredentials;
      
      // Initialize the HTTP client
      httpClient.begin(wifiClient, apiCredentials.ApiUrl);
    }

    /*
     * Execute a GET request on an API endpoint
     * A GET request is an HTTP method that retrieves data from an API server using a URL endpoint
     */
    String GET(String endpoint) {
      // Ensure that there is a wifi connection
      wifiManager.ensureConnection();

      // Create the client to make API calls
      HTTPClient http;
      // Construct the api call target url
      String url = apiCredentials.ApiUrl + endpoint;
      http.begin(url);
      // Add header to identify ourselves in the api call
      http.addHeader(apiCredentials.ApiKeyLabel, apiCredentials.ApiKey);

      // Run the GET api call
      int httpCode = http.GET();
      println("Executing GET request on "+ apiCredentials.Name +": " + url);
      String response = "";
      // Print the response to the serial monitor
      if (httpCode == HTTP_CODE_OK) {
        response = http.getString();
        println("Response code: ");
        print(String(httpCode));
        println("Response message: ");
        print(response);
      } else {
        println("Error in response. Status code: ", "error");
        print(String(httpCode));
        response = http.getString();
        println(response);
      }

      // End the api request and return the result
      http.end();
      println("GET request completed!");
      return response;
    }

  private:
    String Type() {
      return "ApiCaller";
    }

    String ToString() {
      String str = Type() + " - " + apiCredentials.Name + "\n";
      str += "API URL: " + apiCredentials.ApiUrl;
      return str;
    }
};

#endif // BASE
