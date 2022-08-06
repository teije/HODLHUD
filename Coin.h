class Coin
{
  private:
    // Services
    Logger *_logger;
     
  public:
    // Properties
    float amount;
    String symbol;   // Unique currency identifyer of the crypto currency (usually an abbreviation; BTC, ETH, LTC, etc.)
    String title;    // Pretty name for UI purposes 
    float value;     // Trade price at time of purchase (for now by default in EUR)

    Coin(String Symbol, String Title, float Amount = NULL, float Value = NULL) 
    {
      _logger   = new Logger("Coin");
      
      symbol    = Symbol;
      title     = Title;
      amount    = Amount;
      value     = Value;
      
      if(value > 0) {
        _logger->println("New Coin created: ("+ title +") with a value of: " + String(Value) + "EUR");
      } else {
        _logger->println("New Coin created: ("+ title +")");
      }
    }
};
