#ifndef BINANCE_APICALLER_H
#define BINANCE_APICALLER_H

#include "ApiCaller.h"
#include "CurrencyPair.h"
#include <ArduinoJson.h>

class BinanceApiCaller : public ApiCaller {
  public:
    BinanceApiCaller(ApiCredentials apiCredentials, WifiManager wifiManager)
      : ApiCaller(apiCredentials, wifiManager)
    {
      ApiCaller::printCreateMessage();
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
    const String type() override {
      return "BinanceApiCaller.h";
    }
};

#endif // BINANCE_APICALLER_H
