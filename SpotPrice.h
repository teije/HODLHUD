#ifndef SPOTPRICE
#define SPOTPRICE

#include <Arduino.h>
#include "CurrencyPair.h"

class SpotPrice {
  private:
    CurrencyPair currency;
    String timestamp;

  public:
    SpotPrice(CurrencyPair currency, String timestamp) {
      this->currency = currency;
      this->timestamp = timestamp;
    }

    String ToString() {
      return currency.ToString() + ", Timestamp: " + timestamp;
    }

    
    const String toString() override {
      return "SpotPrice.h";
    }

    void SetCurrency(CurrencyPair currency) {
      this->currency = currency;
    }

    CurrencyPair GetCurrency() {
      return this->currency;
    }

    void SetTimestamp(String timestamp) {
      this->timestamp = timestamp;
    }

    String GetTimestamp() {
      return this->timestamp;
    }
};

#endif
