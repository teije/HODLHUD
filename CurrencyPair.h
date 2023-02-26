#ifndef CURRENCYPAIR
#define CURRENCYPAIR

#include "Base.h"

class CurrencyPair: public Base  {
  private:
    String currencyLabel;
    String counterCurrencyLabel;
    float value;

  public:
    CurrencyPair(String currencyLabel, String counterCurrencyLabel, float value) {
      this->currencyLabel = currencyLabel;
      this->counterCurrencyLabel = counterCurrencyLabel;
      this->value = value;

      printCreateMessage();
    }

    const String toString() override {
      return "CurrencyPair.h";
    }

    void setCurrencyLabel(String currencyLabel) {
      this->currencyLabel = currencyLabel;
    }

    String getCurrencyLabel() {
      return this->currencyLabel;
    }

    void setCounterCurrencyLabel(String counterCurrencyLabel) {
      this->counterCurrencyLabel = counterCurrencyLabel;
    }

    String getCounterCurrencyLabel() {
      return this->counterCurrencyLabel;
    }

    void setValue(float value) {
      this->value = value;
    }

    float getValue() {
      return this->value;
    }
};

#endif
