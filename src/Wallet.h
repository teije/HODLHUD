#ifndef WALLET_H
#define WALLET_H

#include "Balance.h"
#include "CurrencyPair.h"

#include <string>

const int MAX_BALANCES = 100; // maximum number of balances in the wallet

class Wallet : public Base {
  public:
    String walletName;
    Balance* balances;
    int balanceCount;

    Wallet(String walletName) {
      this->walletName = walletName;
      this->balanceCount = 0;
      this->balances = new Balance[MAX_BALANCES]; // Allocate memory for balances
    
      println("Created " + Type() + " for " + walletName);
    }

    // This is a destructor?
    ~Wallet() {
      delete[] balances; // Free the allocated memory
    }

    void Add(Balance balance) {
      println("Adding Balance of "+ balance.amountToString() + balance.currencyPair.Label() + " to " + walletName + " wallet");
    
      if (balanceCount < MAX_BALANCES) {
        balances[balanceCount] = balance;
        balanceCount++;
      } else {
        println("Cannot add more balances, reached the maximum limit of " + MAX_BALANCES);
      }
    }

    void Remove(int index) {
      balanceCount--;
      if (index >= 0 && index < balanceCount) {
        for (int i = index; i < balanceCount - 1; i++) {
          balances[i] = balances[i + 1];
        }
        balanceCount--;
      }
    }
    
    void Update(String balanceName, Balance balance) {
      Balance& balanceToUpdate = Get(balanceName);
      if (&balanceToUpdate != NULL) {
        balanceToUpdate = balance;
      }
    }

    Balance& Get(String balanceName) {
      for (int i = 0; i < balanceCount; i++) {
        if (balances[i].Name == balanceName) {
          return balances[i];
        }
      }
      return *(Balance*)nullptr;
    }

    void LoadCryptoBalances() {
      println("Loading Blanaces into the "+ walletName +" wallet");

      CurrencyPair BTC_EUR("BTC", "EUR");
      CurrencyPair ETH_EUR("ETH", "EUR");
      CurrencyPair EUR_USDT("EUR", "USDT");
    
      // Create Balance objects using the currency pairs
      Balance balance_BTC_EUR(BTC_EUR, 4.20);
      Balance balance_ETH_EUR(ETH_EUR, 6.9);
      Balance balance_EUR_USDT(EUR_USDT, 42);
    
      // Add the Balance objects to the Wallet's list of balances
      Add(balance_BTC_EUR);
      Add(balance_ETH_EUR);
      Add(balance_EUR_USDT);

      println("TODO: Add some method to fetch values for all CurrencyPairs in wallet", "todo");
      println("TODO: Write Wallet, Balance and Pairs to SD", "todo");
      
    }


    String Type() {
      return "Wallet";
    }
    
    String ToString() {
      String output = "Type: " + Type() + "\n";
      output += "Name: " + walletName + "\n";
      output += "Number of Balances: " + String(balanceCount) + "\n";
      return output;
    }
};

#endif
