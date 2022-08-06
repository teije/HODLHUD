class Transaction {
  private:
    // Services
    Logger *_logger;
     
  public:
    // Properties
    bool showOnHud;
    Coin *baseCoin;
    Coin *counterCoin;
    String date;
    String remarks;
    float baseValueInEUR;

    Transaction(bool ShowOnHud, Coin *BaseCoin, Coin *CounterCoin, int Day, int Month, int Year, String Remarks, float BaseValueInEUR = 0) {
      _logger         = new Logger("Transaction");
      
      showOnHud       = ShowOnHud;
      baseCoin        = BaseCoin;
      counterCoin     = CounterCoin;
      date            = (String)Day + "/" + (String)Month + "/" + (String)Year;
      remarks         = Remarks;
      baseValueInEUR  = BaseValueInEUR;

      _logger->println("New Transaction created for :" + BaseCoin->symbol + CounterCoin->symbol);
    }
};
