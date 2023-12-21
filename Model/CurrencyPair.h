#ifndef CURRENCYPAIR
#define CURRENCYPAIR

#include "BaseModel.h"

/*
 * Store the Value of a CurrencyPair
 */
class CurrencyPair : public BaseModel  {
  public:
    String ModelId = "D7C689AE-BAE4-4DC1-B4CE-D8B28DD0F996";
    String ModelName = "CurrencyPair";

    String CurrencyLabel;
    String CounterCurrencyLabel;
    float Value;
    uint32_t Timestamp;

    CurrencyPair(String CurrencyLabel, String CounterCurrencyLabel) 
    {
      this->CurrencyLabel = CurrencyLabel;
      this->CounterCurrencyLabel = CounterCurrencyLabel;
    }
    
    CurrencyPair(String CurrencyLabel, String CounterCurrencyLabel, float Value, uint32_t Timestamp = 0) 
    {
      this->CurrencyLabel = CurrencyLabel;
      this->CounterCurrencyLabel = CounterCurrencyLabel;
      this->Value = Value;
      this->Timestamp = Timestamp;
    }

    String Label()
    {
      return CurrencyLabel+CounterCurrencyLabel;
    }

    String ValueToString()
    {
      return String(Value);
    }

  private:

};

#endif
