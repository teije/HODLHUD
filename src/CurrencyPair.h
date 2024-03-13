#ifndef CURRENCYPAIR
#define CURRENCYPAIR

#include "Base.h"

#include <string>

/*
 * Store the value of a CurrencyPair
 */
class CurrencyPair : public Base  {
  public:
    String currencyLabel;
    String counterCurrencyLabel;
    float value;
    uint32_t timestamp;

    CurrencyPair(String currencyLabel, String counterCurrencyLabel) 
    {
      this->currencyLabel = currencyLabel;
      this->counterCurrencyLabel = counterCurrencyLabel;
    }
    
    CurrencyPair(String currencyLabel, String counterCurrencyLabel, float value, uint32_t timestamp = 0) 
    {
      this->currencyLabel = currencyLabel;
      this->counterCurrencyLabel = counterCurrencyLabel;
      this->value = value;
      this->timestamp = timestamp;

      println("Created " + Type() + " for " + Label() + " with value " + ValueToString());
    }

    String Label()
    {
      return currencyLabel+counterCurrencyLabel;
    }

    String ValueToString()
    {
      return String(value);
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
