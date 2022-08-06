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
      _logger   = new Logger();
      
      symbol    = Symbol;
      title     = Title;
      amount    = Amount;
      value     = Value;

      _logger->setSourceName("Coin");
      _logger->print("New Coin created: ("+ title +")");
      
      if(value > 0) {
        _logger->print(" with a value price of: " + String(Value) + "EUR");
      }
    }
};
