#ifndef CURRENCYPAIR
#define CURRENCYPAIR

#include "Base.h"

class CurrencyPair: public Base  {
  private:

  public:
    CurrencyPair(String currencyLabel, String counterCurrencyLabel, float value) {
      this->currencyLabel = currencyLabel;
      this->counterCurrencyLabel = counterCurrencyLabel;
      this->value = value;

      printCreateMessage();
    }

    const String type() override {
      return "CurrencyPair.h";
    }

    String currencyLabel;
    String counterCurrencyLabel;
    float value;
};

#endif
