#ifndef BINANCE_APICALLER_H
#define BINANCE_APICALLER_H

#include "ApiCaller.h"
#include "CurrencyPair.h"
#include <ArduinoJson.h>

class BinanceApiCaller : public ApiCaller {
  public:
    BinanceApiCaller(ApiCredentials apiCredentials, WifiManager wifiManager) : ApiCaller(apiCredentials, wifiManager)
    {
      
    }

    CurrencyPair getCurrentPrice(const char* currencyLabel, const char* counterCurrencyLabel) {
      // Construct the endpoint with the given currency labels and timestamp
      String endpoint = "/api/v3/ticker/price?symbol=" +
                        String(currencyLabel) +
                        String(counterCurrencyLabel);

      // Send the GET request and get the response string
      String response = GET(endpoint);

      // Parse the response string into a JSON object
      StaticJsonDocument<256> doc;
      deserializeJson(doc, response);

      // Parse JSON response
      float value = doc["price"];
    
      // Create and return CurrencyPair object
      CurrencyPair pair(currencyLabel, counterCurrencyLabel, value);
      return pair;
    }

  private:
    String Type() {
      return "BinanceApiCaller";
    }

    String ToString() {
      String output = Type() + " - " + apiCredentials.name + "\n";
      output += "API URL: " + apiCredentials.apiUrl + "\n";
      return output;
    }
};

#endif // BINANCE_APICALLER_H
