#ifndef BINANCE_APICALLER_H
#define BINANCE_APICALLER_H

#include "ApiCaller.h"
#include "CurrencyPair.h"
#include <ArduinoJson.h>

class BinanceApiCaller : public ApiCaller {
  public:
    BinanceApiCaller(WiFiManager wifiManager) : ApiCaller(apiCredentials, wifiManager)
    {
      this->apiCredentials = SettingsManager::GetApiCredentialByName("Binance");
    }

    /*
     * Get the current price of a currency pair
     */
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
      String value = doc["price"];
    
      // Create and return CurrencyPair object
      CurrencyPair pair(currencyLabel, counterCurrencyLabel, value);
      return pair;
    }

    /*
     * Get the price of a currency pair at a (historical) timestamp
     */
    CurrencyPair getHistoricalPrice(const char* currencyLabel, const char* counterCurrencyLabel, uint64_t timestamp) {
      // Construct the endpoint with the given currency labels and timestamp
      String endpoint = "/api/v3/klines?symbol=" +
                        String(currencyLabel) +
                        String(counterCurrencyLabel) +
                        "&interval=1m" +
                        "&startTime=" +
                        String(timestamp) +
                        "&endTime=" +
                        String(timestamp + 1);

      // Send the GET request and get the response string
      String response = GET(endpoint);

      // Parse the response string into a JSON object
      StaticJsonDocument<1024> doc;
      deserializeJson(doc, response);

      // Get the closing price from the klines array
      String value = doc[0][4];

      // Create and return CurrencyPair object
      CurrencyPair pair(currencyLabel, counterCurrencyLabel, value);
      return pair;
    }


  private:
    String Type() {
      return "BinanceApiCaller";
    }

    String ToString() {
      String output = Type() + " - " + apiCredentials.Name + "\n";
      output += "API URL: " + apiCredentials.ApiUrl + "\n";
      return output;
    }
};

#endif // BINANCE_APICALLER_H
