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

      _logger->println("New TransactionService created");
    }

    int getTransactionCount() {
      return _apiCaller->getTransactionCount();
    }

    Transaction * getTransactions() {
      return _apiCaller->getTransactions();
    }
};
