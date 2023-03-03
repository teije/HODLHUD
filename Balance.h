#ifndef APICALLER
#define APICALLER

class Balance {
  public:
    CurrencyPair currencyPair;
    float amount;

    Balance(CurrencyPair currencyPair, float amount) {
      this->currencyPair = currencyPair;
      this->amount = amount;
    }

  private:
    String Type() {
      return "Balance";
    }

  public:
    String ToString() {
      String output = "Type: " + Type() + "\n";
      output += "Currency Pair: " + currencyPair.currencyLabel + "/" + currencyPair.counterCurrencyLabel + "\n";
      output += "Amount: " + String(amount) + "\n";
      return output;
    }
};

#endif
