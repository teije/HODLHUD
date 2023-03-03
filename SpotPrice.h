#ifndef SPOTPRICE
#define SPOTPRICE

#include <Arduino.h>
#include "CurrencyPair.h"

class SpotPrice : public Base{
  public:
    CurrencyPair currency;
    String timestamp;

    SpotPrice(CurrencyPair currency, String timestamp) {
      this->currency = currency;
      this->timestamp = timestamp;

      printCreateMessage();
    }

    String Type() {
      return "SpotPrice.h";
    }

    String ToString() {
      return "Currency Pair: " + currency.currencyLabel + "/" + currency.counterCurrencyLabel + "for Timestamp: " + timestamp;
    }
};

#endif
