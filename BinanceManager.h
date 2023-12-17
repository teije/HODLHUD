//#ifndef BINANCE_MANAGER_H
//#define BINANCE_MANAGER_H
//
//#include "BinanceApiCaller.h"
//#include "CurrencyPair.h"
//#include "ESP32Clock.h"
//#include "JsonParser.h"
//#include "SDManager.h"
//
//class BinanceManager : public Base {
//  public:
//       
//    BinanceManager(BinanceApiCaller& binanceApiCaller, SDManager& sdManager, ESP32Clock& internalClock) : binanceApiCaller(binanceApiCaller), sdManager(sdManager), internalClock(internalClock)
//    { 
//      sdIsReady = sdManager.initialize();
//      if (sdIsReady)
//      {
//        //sdManager.runExampleOperations();
//      }
//    }
//
//    /*
//       Get the current price of a currency pair
//    */
//    CurrencyPair getCurrentPrice(const char * currencyLabel, const char* counterCurrencyLabel) {
//      // Get the current price for the label pair
//      CurrencyPair currentPrice = binanceApiCaller.getCurrentPrice(currencyLabel, counterCurrencyLabel);
//
//      sdManager.createFolder("path to folder");
//
//      // Save the value to the SD card
//      sdManager.createFile(
//        String("binance/" + String(currencyLabel) + String(counterCurrencyLabel) + "/" + String(internalClock.getUnixTimestamp())),
//        String(currentPrice.value)
//      );
//      
//      return currentPrice;
//    }
//
//    /*
//       Get the price of a currency pair at a (historical) timestamp
//    */
//    CurrencyPair getHistoricalPrice(const char* currencyLabel, const char* counterCurrencyLabel, uint64_t timestamp) {
//      // TODO: Try get CurrencyPair from SD card
//      //        [ ] Define folder structure:
//      //            [ ] format:  /source  /type /label /year_month_day_hour_minute.txt
//      //                example: /binance /price/EURETH/2023_03_23_11_09.txt
//      //
//      //        [ ] Read file-data from SD card using format above
//      //            [ ] If no file is found, fallback to API fetching
//      //
//      //        [ ] Parse file-data to CurrencyPair?
//      //        [ ]
//      //
//
//      // TODO: Try get CurrencyPair from API
//      //       [ ]
//
//      return binanceApiCaller.getHistoricalPrice(currencyLabel, counterCurrencyLabel, timestamp);
//    }
//
//  private:
//    String Type() {
//      return "BinanceManager";
//    }
//    BinanceApiCaller& binanceApiCaller;
//    ESP32Clock internalClock;
//    JsonParser jsonParser;
//    SDManager& sdManager;
//
//    bool sdIsReady = false;
//};
//
//#endif // BINANCE_MANAGER_H
