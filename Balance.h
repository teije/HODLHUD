#ifndef BALANCE
#define BALANCE

#include "CurrencyPair.h"

class Balance : public Base {
  public:
    float amount;
    CurrencyPair currencyPair;
    String Name;

    Balance(CurrencyPair currencyPair, float amount) : currencyPair(currencyPair), amount(amount) 
    {
      this->Name = currencyPair.Label();

      println("Created " + Name + " " + Type());
    }

  private:

  public:
    String Type() {
      return "Balance";
    }
    
    String ToString() {
      String output = "Type: " + Type() + "\n";
      output += "Currency Pair: " + currencyPair.currencyLabel + "/" + currencyPair.counterCurrencyLabel + "\n";
      output += "Amount: " + String(amount) + "\n";
      return output;
    }
};

#endif
