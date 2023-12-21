#ifndef WALLET
#define WALLET

#include "Balance.h"
#include "CurrencyPair.h"

const int MAX_BALANCES = 100; // maximum number of Balances in the wallet

class Wallet : public BaseModel {
  public:
    String ModelId = "C9C84952-025C-407A-940D-37689B7AC729";
    String ModelName = "Wallet";

    String Name;
    Balance* Balances;
    int CurrentBalanceCount;

    Wallet(String Name) {
      this->Name = Name;
      this->CurrentBalanceCount = 0;
      this->Balances = new Balance[MAX_BALANCES]; // Allocate memory for Balances
    }

    // This is a destructor?
    ~Wallet() {
      delete[] Balances; // Free the allocated memory
    }

    void Add(Balance balance) {
      //println("Adding Balance of "+ balance.amountToString() + balance.currencyPair.Label() + " to " + Name + " wallet");
    
      if (CurrentBalanceCount < MAX_BALANCES) {
        Balances[CurrentBalanceCount] = balance;
        CurrentBalanceCount++;
      } else {
        //println("Cannot add more Balances, reached the maximum limit of " + MAX_BALANCES);
      }
    }

    void Remove(int index) {
      CurrentBalanceCount--;
      if (index >= 0 && index < CurrentBalanceCount) {
        for (int i = index; i < CurrentBalanceCount - 1; i++) {
          Balances[i] = Balances[i + 1];
        }
        CurrentBalanceCount--;
      }
    }
    
    void Update(String balanceName, Balance balance) {
      Balance& balanceToUpdate = Get(balanceName);
      if (&balanceToUpdate != NULL) {
        balanceToUpdate = balance;
      }
    }

    Balance& Get(String balanceName) {
      for (int i = 0; i < CurrentBalanceCount; i++) {
        if (Balances[i].Name == balanceName) {
          return Balances[i];
        }
      }
      return *(Balance*)nullptr;
    }

    void LoadCryptoBalances() {
      CurrencyPair BTC_EUR("BTC", "EUR");
      CurrencyPair ETH_EUR("ETH", "EUR");
      CurrencyPair EUR_USDT("EUR", "USDT");
    
      // Create Balance objects using the currency pairs
      Balance balance_BTC_EUR(BTC_EUR, 4.20);
      Balance balance_ETH_EUR(ETH_EUR, 6.9);
      Balance balance_EUR_USDT(EUR_USDT, 42);
    
      // Add the Balance objects to the Wallet's list of Balances
      Add(balance_BTC_EUR);
      Add(balance_ETH_EUR);
      Add(balance_EUR_USDT);      
    }
};

#endif
