#ifndef WALLET_H
#define WALLET_H

#include "Balance.h"
#include "CurrencyPair.h"

const int MAX_BALANCES = 100; // maximum number of balances in the wallet

class Wallet : public Base {
  public:
    String name;
    Balance* balances;
    int balanceCount;

    Wallet(String name) {
      this->name = name;
      this->balanceCount = 0;
      this->balances = nullptr; // initialize to nullptr

      println("Created " + name + " " + Type());
    }

    void Add(Balance balance) {
      println("Adding Balance to " + name + " wallet");
      
      if (balanceCount < MAX_BALANCES) {
        balances[balanceCount] = balance;
        balanceCount++;
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

    /*
     * This method is a placeholder until we can read from the SD card
     * WARNING: Using this method currently breaks something in the memory
     *          Probably should not use this an donly use it for reference
     */
    void LoadCryptoBalances() {
      println("Loading Blanaces into the "+ name +" wallet");
      
      // Create currency pairs
      CurrencyPair usdEur("USD", "EUR", 0.85);
    
      // Create Balance objects using the currency pairs
      Balance balance(usdEur, 100.0);
    
      // Add the Balance objects to the Wallet's list of balances
      Add(balance);
    }


    String Type() {
      return "Wallet";
    }
    
    String ToString() {
      String output = "Type: " + Type() + "\n";
      output += "Name: " + name + "\n";
      output += "Number of Balances: " + String(balanceCount) + "\n";
      return output;
    }
};

#endif
