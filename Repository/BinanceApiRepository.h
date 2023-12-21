#ifndef BINANCE_API_REPOSITORY
#define BINANCE_API_REPOSITORY

#include "BaseApiRepository.h"
#include "../Model/CurrencyPair.h"

#include <ArduinoJson.h>

class BinanceApiRepository : public BaseApiRepository {
  public:
    BinanceApiRepository(WiFiManager wifiManager) : BaseApiRepository(apiCredentials, wifiManager)
    {
      this->apiCredentials = SettingsManager::GetApiCredentialByName("Binance");
    }

    /*
     * Get the current price of a currency pair
     */
    CurrencyPair GetCurrentPrice(const char* currencyLabel, const char* counterCurrencyLabel) {
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

    /*
     * Get the price of a currency pair at a (historical) timestamp
     */
    CurrencyPair GetHistoricalPrice(const char* currencyLabel, const char* counterCurrencyLabel, uint64_t timestamp) {
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
      float value = doc[0][4].as<float>();

      // Create and return CurrencyPair object
      CurrencyPair pair(currencyLabel, counterCurrencyLabel, value);
      return pair;
    }


  private:
    
};

#endif
