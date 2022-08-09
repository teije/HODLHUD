class TransactionService
{
  private:
    // Services
    ApiCaller *_apiCaller;
    Logger *_logger;
    
  public:
    // Properties

    TransactionService(ApiCaller *apiCaller) {
      _apiCaller = apiCaller;
      _logger = new Logger("TransactionService");

      //_logger->println("New TransactionService created");
    }

    int getTransactionCount() {
      return _apiCaller->getTransactionCount();
    }

    Transaction * getTransactions() {
      String response = _apiCaller->getTransactions();

      DynamicJsonDocument jsonObject(1024);   // Reserving memory space to hold the json object
      deserializeJson(jsonObject, response);  // Converting from a string to a json object

      int transactionCount = getTransactionCount();
      Transaction *transactions[transactionCount];

      for (int i=0; i<transactionCount; i++) {
        bool showOnHud        = jsonObject["values"][i][0].as<bool>();
        String baseName       = jsonObject["values"][i][1].as<String>();
        String baseSymbol     = jsonObject["values"][i][2].as<String>();
        float baseAmount      = jsonObject["values"][i][3].as<float>();
        String counterName    = jsonObject["values"][i][4].as<String>();
        String counterSymbol  = jsonObject["values"][i][5].as<String>();
        float counterAmount   = jsonObject["values"][i][6].as<float>();
        String date           = jsonObject["values"][i][7].as<String>();
        String remarks        = jsonObject["values"][i][8].as<String>();

        int day   = String(date[0] + date[1]).toInt();
        int month = String(date[3] + date[4]).toInt();
        int year  = String(date[6] + date[7] + date[8] + date[9]).toInt();

        Coin *baseCoin    = new Coin(baseSymbol, baseName, baseAmount);
        Coin *counterCoin = new Coin(counterSymbol, counterName, counterAmount);

        transactions[i] = new Transaction(
          showOnHud,
          baseCoin, counterCoin,
          day, month, year,
          remarks
          );
      }

      return *transactions;
    }
};
