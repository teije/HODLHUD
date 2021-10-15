class CurrencyPair
{
  private:
    Logger* logger = new Logger("CurrencyPair");
     
  public:
    String baseCurrency;    // Unique currency identifyer of the crypto currency (usually an abbreviation; BTC, ETH, LTC, etc.) 
    String counterCurrency; // Base currency in which the exchange rate is defined
    float spotPrice;        // Exchange price (in the baseCurrency)

    CurrencyPair(String BaseCurrency, String CounterCurrency, float SpotPrice) {
      baseCurrency = BaseCurrency;
      counterCurrency = CounterCurrency;
      spotPrice = SpotPrice;

      logger->print("New CurrencyPair created: (" + baseCurrency + "/"+ counterCurrency +") with a spot price of: " + String(spotPrice) + baseCurrency);
    }
};
