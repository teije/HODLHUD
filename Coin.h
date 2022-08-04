class Coin
{
  private:
    // Services
    Logger* logger = new Logger("Coin");
     
  public:
    // Properties
    float amount;
    String symbol;    // Unique currency identifyer of the crypto currency (usually an abbreviation; BTC, ETH, LTC, etc.)
    String title;      // Pretty name for UI purposes 
    float spotPrice;  // Trade price (for now by default in EUR)

    Coin(String Symbol, String Title, float Amount = NULL, float SpotPrice = NULL) {
      symbol    = Symbol;
      title     = Title;
      amount    = Amount;
      spotPrice = SpotPrice;

      logger->print("New Coin created: ("+ title +")");
      
      if(spotPrice > 0) {
        logger->print(" with a spot price of: " + String(spotPrice) + symbol);
      }
    }
};
