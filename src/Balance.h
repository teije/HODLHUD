#ifndef BALANCE
#define BALANCE

#include "CurrencyPair.h"

#include <string>

class Balance : public Base {
public:
    float amount;
    CurrencyPair currencyPair;
    String Name;

    // Default constructor (for initializing the list of balances in the wallet, won't work without default constructor)
    Balance() : amount(0.0), currencyPair(CurrencyPair("<balance-placeholder>", "")) {}
    
    // Parameterized constructor
    Balance(CurrencyPair currencyPair, float amount) : currencyPair(currencyPair), amount(amount)
    {
        this->Name = currencyPair.Label();
        println("Created " + Type() + " for " + Name);
    }

    String amountToString()
    {
      return String(amount);
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
