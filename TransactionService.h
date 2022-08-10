class TransactionService
{
  private:
    // Services
    ApiCaller *_apiCaller;
    
  public:
    TransactionService(ApiCaller *apiCaller) {
      _apiCaller = apiCaller;
    }

    int getTransactionCount() {
      return _apiCaller->getTransactionCount();
    }

    String getTransactions() {
      return _apiCaller->getTransactions();
    }
};
