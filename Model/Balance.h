#ifndef BALANCE
#define BALANCE

#include "CurrencyPair.h"

class Balance : public BaseModel {
public:
    String ModelId = "58E58DDC-F8BC-49B8-B0AB-A27B6A56C0D4";
    String ModelName = "Balance";

    float Amount;
    CurrencyPair Pair;
    String Name;

    // Default constructor (for initializing the list of balances in the wallet, won't work without default constructor)
    Balance() : Amount(0.0), Pair(CurrencyPair("<balance-placeholder>", "")) {}
    
    // Parameterized constructor
    Balance(CurrencyPair pair, float amount) : Pair(pair), Amount(amount)
    {
        this->Name = pair.Label();
        this->Pair = pair;
        this->Amount = amount;
    }

    String AmountToString()
    {
      return String(Amount);
    }

private:

};

#endif
