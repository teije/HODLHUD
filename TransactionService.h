class TransactionService
{
  private:
    // Services
    ApiCaller *_apiCaller;
    CoinService *_coinService;
  
    // Constants
    const int TRANSACTION_FIELD_COUNT = 10;
    const char* variable_labels[10]   = {
      "Show on HUD",
      "Base title",
      "Base symbol",
      "Base amount",
      "Counter title",
      "Counter symbol",
      "Counter amount",
      "Date",
      "Remarks",
      "Value in EUR",
    };
    
    const int TRANSACTION_SHOW_ON_HUD    = 0;
    const int TRANSACTION_BASE_TITLE     = 1;
    const int TRANSACTION_BASE_SYMBOL    = 2;
    const int TRANSACTION_BASE_AMOUNT    = 3;
    const int TRANSACTION_COUNTER_TITLE  = 4;
    const int TRANSACTION_COUNTER_SYMBOL = 5;
    const int TRANSACTION_COUNTER_AMOUNT = 6;
    const int TRANSACTION_DATE           = 7;
    const int TRANSACTION_REMARKS        = 8;
    const int TRANSACTION_VALUE_IN_EUR   = 9;
    
  public:
    TransactionService(ApiCaller *apiCaller, CoinService *coinService) {
      _apiCaller   = apiCaller;
      _coinService = coinService;
    }

    /* Get the total count of transactions defined in the Google Sheet */
    int getTransactionCount() {
      return _apiCaller->getTransactionCount();
    }

    /* Get all transactions defined in the Google Sheet */
//    String getTransactions() {
//      return _apiCaller->getTransactions();
//    }

    /* Get all transactions defined in the Google Sheet */
    JsonArray getTransactions() {
      int transactionCount      = getTransactionCount();                            // Fetch number of transactions in the google sheet
      int transactionObjectSize = 300;                                              // In JSON a transaction costs about 300 memory units
      int jsonDocumentSize      = transactionCount * transactionObjectSize;         // Calculate the size by multiplying the units per transaction * amount of transactions
      String responseString     = _apiCaller->getTransactions();                    // Grabbing transactions from the Google Sheet as a json string
    
      DynamicJsonDocument jsonDocument(jsonDocumentSize);                           // Reserving memory space to hold the json object
      DeserializationError error = deserializeJson(jsonDocument, responseString);   // Converting from the api response string to a json object we can work with
    
      if (error) {                                                                  // Throw error if serialization fails (happens usually when loading too many transactions - so far >~200)
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
      }
      jsonDocument.shrinkToFit();                                                    // Shrink memory size to fit the content & to not waste any memory
    
      JsonArray jsonValuesArray = jsonDocument["values"];
      return jsonValuesArray;
    }

    void fillValues() {
      JsonArray transactionsJsonArray = getTransactions();
      
      for (int i=0; i<transactionsJsonArray.size(); i++) {                                 // Print all values for each transaction
        if (transactionsJsonArray[i][TRANSACTION_VALUE_IN_EUR]) {
          Serial.println('.');
        } else {
          float valueInEUR = _coinService->getSpotValue(transactionsJsonArray[i][TRANSACTION_BASE_SYMBOL]);
          Serial.println(valueInEUR, 5);
        }
      }
    }
};
