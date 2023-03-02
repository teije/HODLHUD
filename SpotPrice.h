#ifndef SPOTPRICE
#define SPOTPRICE

#include <Arduino.h>
#include "CurrencyPair.h"

class SpotPrice {
  public:
    CurrencyPair currency;
    String timestamp;

    SpotPrice(CurrencyPair currency, String timestamp) {
      this->currency = currency;
      this->timestamp = timestamp;
    }

    String ToString() {
      return currency.ToString() + ", Timestamp: " + timestamp;
    }

    const String type() override {
      return "SpotPrice.h";
    }
};

#endif
