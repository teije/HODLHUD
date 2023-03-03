#ifndef WALLET_H
#define WALLET_H

#include "Balance.h"

const int MAX_BALANCES = 100; // maximum number of balances in the wallet

class Wallet {
  public:
    String name;
    Balance balances[MAX_BALANCES];
    int balanceCount;

    Wallet(String name) {
      this->name = name;
      this->balanceCount = 0;
    }

    void Add(Balance balance) {
      if (balanceCount < MAX_BALANCES) {
        balances[balanceCount] = balance;
        balanceCount++;
      }
    }

    void Remove(int index) {
      if (index >= 0 && index < balanceCount) {
        for (int i = index; i < balanceCount - 1; i++) {
          balances[i] = balances[i + 1];
        }
        balanceCount--;
      }
    }
    
    void Update(String balanceName, Balance balance) {
      Balance* balanceToUpdate = Get(balanceName);
      if (balanceToUpdate != nullptr) {
        *balanceToUpdate = balance;
      }
    }

    Balance* Get(String balanceName) {
      for (int i = 0; i < balanceCount; i++) {
        if (balances[i].name == balanceName) {
          return &balances[i];
        }
      }
      return nullptr;

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
