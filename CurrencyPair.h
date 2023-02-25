#ifndef CURRENCYPAIR
#define CURRENCYPAIR

#include "Base.h"

class CurrencyPair: public Base  {
  private:
    String currencyLabel;
    String counterCurrencyLabel;
    float counterValue;

  public:
    CurrencyPair(String currencyLabel, String counterCurrencyLabel, float counterValue) {
      this->currencyLabel = currencyLabel;
      this->counterCurrencyLabel = counterCurrencyLabel;
      this->counterValue = counterValue;

      printCreateMessage();
    }

    const String toString() override {
      return currencyLabel + "-" + counterCurrencyLabel + ": " + String(counterValue);
    }

    void SetCurrencyLabel(String currencyLabel) {
      this->currencyLabel = currencyLabel;
    }

    String GetCurrencyLabel() {
      return this->currencyLabel;
    }

    void SetCounterCurrencyLabel(String counterCurrencyLabel) {
      this->counterCurrencyLabel = counterCurrencyLabel;
    }

    String GetCounterCurrencyLabel() {
      return this->counterCurrencyLabel;
    }

    void SetCounterValue(float counterValue) {
      this->counterValue = counterValue;
    }

    float GetCounterValue() {
      return this->counterValue;
    }
};

#endif
