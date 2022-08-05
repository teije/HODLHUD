class Coin
{
  private:
    // Services
    Logger* logger = new Logger("Coin");
     
  public:
    // Properties
    float amount;
    String symbol;   // Unique currency identifyer of the crypto currency (usually an abbreviation; BTC, ETH, LTC, etc.)
    String title;    // Pretty name for UI purposes 
    float value;     // Trade price at time of purchase (for now by default in EUR)

    Coin(String Symbol, String Title, float Amount = NULL, float Value = NULL) {
      symbol    = Symbol;
      title     = Title;
      amount    = Amount;
      value     = Value;

//      logger->print("New Coin created: ("+ title +")");
//      
//      if(value > 0) {
//        logger->print(" with a value price of: " + String(Value) + "EUR");
//      }
    }
};

Een transaction heeft:
    bool showOnHud;
    Coin *baseCoin;
    Coin *counterCoin;
    String date;
    String remarks;
    float baseValueInEUR;

Een coin heeft:
    float amount;
    String symbol;  
    String title; 
    float value;
