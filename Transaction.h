class Transaction {
  private:
    // Services
    Logger* logger = new Logger("Transaction");
     
  public:
    // Properties
    bool showOnHud;
    Coin *baseCoin;
    Coin *counterCoin;
    String date;
    String remarks;
    float baseValueInEUR;

    Transaction(bool ShowOnHud, Coin *BaseCoin, Coin *CounterCoin, int Day, int Month, int Year, String Remarks, float BaseValueInEUR = 0) {
      showOnHud       = ShowOnHud;
      baseCoin        = BaseCoin;
      counterCoin     = CounterCoin;
      date            = (String)Day + "/" + (String)Month + "/" + (String)Year;
      remarks         = Remarks;
      baseValueInEUR  = BaseValueInEUR;

      logger->print("New Transaction created for :" + BaseCoin->symbol + CounterCoin->symbol);
    }
};
