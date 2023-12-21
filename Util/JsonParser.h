#ifndef JSON_PARSER
#define JSON_PARSER

#include "../Model/CurrencyPair.h"
#include <ArduinoJson.h>

class JsonParser {
  public:
    JsonParser() { }

    // Parse a Binance price ({"symbol":"BTCEUR","price":"22746.00000000"}) into a CurrencyPair object
    static CurrencyPair JsonToCurrencyPair(String json, String currencyLabel, String counterCurrencyLabel) {

      StaticJsonDocument<128> doc;
      deserializeJson(doc, json);

      float counterValue = doc["price"].as<float>();

      return CurrencyPair(currencyLabel, counterCurrencyLabel, counterValue);
    }

  private:
};

#endif
