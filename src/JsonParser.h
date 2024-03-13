#ifndef JSONPARSER
#define JSONPARSER

/** HODLHUD CLASSES */
#include "Base.h"
#include "CurrencyPair.h"

/** EXTERNAL LIBRARIES */
#include <ArduinoJson.h>
#include <string>

class JsonParser : public Base {
  public:
    JsonParser()
    {
      println("Created...");
      println("TODO: Handle error when parsing fails", "warning"); 
    }

  
    // Parse a Binance price ({"symbol":"BTCEUR","price":"22746.00000000"}) into a CurrencyPair object
    static CurrencyPair parseCurrencyPair(String json, String currencyLabel, String counterCurrencyLabel) {

      JsonDocument doc;
      deserializeJson(doc, json);

      float counterValue = doc["price"].as<float>();

      return CurrencyPair(currencyLabel, counterCurrencyLabel, counterValue);
    }

  private:
    String Type() {
      return "JsonParser";
    }
};

#endif
