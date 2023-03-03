#ifndef CURRENCYPAIR
#define CURRENCYPAIR

#include "Base.h"

class CurrencyPair : public Base  {
  public:
    String currencyLabel;
    String counterCurrencyLabel;
    float value;
    
    CurrencyPair(String currencyLabel, String counterCurrencyLabel, float value) {
      this->currencyLabel = currencyLabel;
      this->counterCurrencyLabel = counterCurrencyLabel;
      this->value = value;

    }

  private:
    String Type() {
      return "CurrencyPair";
    }

    String ToString() {
      String output = "Type: " + Type() + "\n";
      output += "Currency Label: " + currencyLabel + "\n";
      output += "Counter Currency Label: " + counterCurrencyLabel + "\n";
      output += "Value: " + String(value) + "\n";
      return output;
    }

};

#endif
