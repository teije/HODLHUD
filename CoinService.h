class CoinService
{
  private:
    // Services
    ApiCaller *_apiCaller;

    // Constants
    const String COIN_SYMBOL_USDT = "USDT";
    
  public:
    // Properties

    CoinService(ApiCaller *apiCaller) {
      _apiCaller = apiCaller;
    }

    float getSpotValue(String baseSymbol) {
      String response = _apiCaller->executeBinance("/api/v3/ticker/price", "?symbol=" + baseSymbol + COIN_SYMBOL_USDT);
      
      DynamicJsonDocument jsonObject(1024);   // Reserving memory space to hold the json object
      deserializeJson(jsonObject, response);  // Converting from a string to a json object
      float value = jsonObject["price"];      // Grab value from json object

      return value;
    }

    void * getMultipleSpotValues(String * baseSymbols) {
      // Building a string like this: ["BTCUSDT","BNBUSDT"] 
      String symbolString = "[";

      for(int i=0; i<baseSymbols->length(); i++) {
        symbolString += '"' + (baseSymbols[i] + COIN_SYMBOL_USDT) + '"' + ",";
      }

      symbolString += "]";
      
      String response = _apiCaller->executeBinance("/api/v3/ticker/price", "?symbol=" + symbolString);
      
      DynamicJsonDocument jsonObject(1024);   // Reserving memory space to hold the json object
      deserializeJson(jsonObject, response);  // Converting from a string to a json object
      //float value = jsonObject["price"];      // Grab value from json object    
    }
};
