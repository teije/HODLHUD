class Coin
{
  private:
    // Services
    Logger *_logger;
     
  public:
    Coin(String Abbreviation, String Title, float Amount = NULL, float Value = NULL) 
    {
      _logger   = new Logger("Coin");
      if(value > 0) {
        //_logger->println("New Coin created: ("+ title +") with a value of: " + String(Value) + "EUR");
      } else {
        //_logger->println("New Coin created: ("+ title +")");
      }
      abbreviation  = Abbreviation;
      title         = Title;
      amount        = Amount;
      value         = Value;
    }

    // Properties
    float amount;
    String abbreviation;  // Unique currency identifyer of the crypto currency (usually an abbreviation; BTC, ETH, LTC, etc.)
    String title;         // Pretty name for UI purposes 
    float value;          // Trade price at time of purchase (for now by default in EUR)
};
