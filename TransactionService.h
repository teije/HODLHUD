class TransactionService
{
  private:
    // Services
    ApiCaller *_apiCaller;
    
  public:
    TransactionService(ApiCaller *apiCaller) {
      _apiCaller = apiCaller;
    }

    /* Get the total count of transactions defined in the Google Sheet */
    int getTransactionCount() {
      return _apiCaller->getTransactionCount();
    }

    /* Get all transactions defined in the Google Sheet */
    String getTransactions() {
      return _apiCaller->getTransactions();
    }
};
