#ifndef BINANCE_APICALLER
#define BINANCE_APICALLER

#include "ApiCaller.h"
#include "CurrencyPair.h"
#include <ArduinoJson.h>

class BinanceApiCaller : public ApiCaller, Base {
  public:
    BinanceApiCaller(ApiCredentials apiCredentials, WifiManager wifiManager) : ApiCaller(apiCredentials, wifiManager) 
    {
      ApiCaller::printCreateMessage();
    }

    CurrencyPair getCurrencyPair(const char* currencyLabel, const char* counterCurrencyLabel, time_t startTime = 0) {
      // Use current time if startTime is not provided or is equal to 0
      if (startTime == 0) {
        startTime = time(nullptr);
      }

      // Calculate the end time as 1 minute before the start time
      time_t endTime = startTime - 60;

      // Construct the endpoint with the given currency labels and timestamps
      String endpoint = "/api/v3/klines?symbol=" + String(currencyLabel) + String(counterCurrencyLabel) + "&interval=1d&startTime=" + String(startTime * 1000) + "&endTime=" + String(endTime * 1000);

      // Send the GET request and get the response string
      String response = GET(endpoint);

      // Parse the response string into a JSON object
      StaticJsonDocument<256> doc;
      deserializeJson(doc, response);

      // Get the last entry in the klines array (which is the most recent day)
      JsonArray klines = doc.as<JsonArray>();
      JsonObject lastEntry = klines[klines.size() - 1].as<JsonObject>();

      // Get the open price from the last entry
      float openPrice = lastEntry["1"].as<float>();

      // Create and return a CurrencyPair object with the extracted values
      return CurrencyPair(currencyLabel, counterCurrencyLabel, openPrice);
    }

    private:  
      const String toString() override {
        return "BinanceApiCaller.h";
      }
};

#endif // BINANCE_APICALLER_H
