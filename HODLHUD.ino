// External classes
#include <string.h>

// Project classes
#include "Model/CurrencyPair.h"
#include "Model/Balance.h"
#include "Model/Wallet.h"

#include "Repository/BinanceApiRepository.h"
#include "Repository/StorageRepository.h"

#include "Util/InternalClock.h"
#include "Util/JsonParser.h"
#include "Util/SettingsManager.h"
#include "Util/WiFiManager.h"
#include "Util/WirelessUpdateManager.h"


StorageRepository StorageRepository;
WiFiManager WifiManager;
BinanceApiRepository BinanceApiRepository(WifiManager);
InternalClock InternalClock(WifiManager);
WirelessUpdateManager WirelessUpdateManager(WifiManager);

int baudrate = 115200;
// TODO:
// [ ] Setup services instead of using repositories
// [ ] 

void setup()
{
  // Set Baudrate
  Serial.begin(baudrate);
  Serial.println("Setup start");

  // Configure WiFi Network
  WifiManager.Connect();
  Serial.println("Configured WiFi manager: " + WifiManager.connectedNetworkSsid);

  // Configure the ability to do wireless updates
  WirelessUpdateManager.begin();
  
  // Create a new instance of the Binance API caller
  //println("Configuring Binance API caller");

  // Get the Unix timestamp (for API calls)
  uint32_t unixTime = InternalClock.GetUnixTimestamp();
  // Get the current time in human-readable format (for UI)
  String timeStr = InternalClock.GetHumanReadableDateTime();

  // Get the current BTC/EUR price
  CurrencyPair currentPrice = BinanceApiRepository.GetCurrentPrice("BTC", "EUR");
  String message_currentPrice = "Current BTC/EUR price: " + currentPrice.ValueToString();
  //println(message_currentPrice);

  String historicalReadableTime = "2012-09-14 12:00:00";
  uint32_t historicalUnixTime = InternalClock.ParseHumanReadableTimeToUnix(historicalReadableTime);
  CurrencyPair historicalPrice = BinanceApiRepository.GetHistoricalPrice("BTC", "EUR", 1646400000000);

  String message_historicalPrice = "Historical BTC/EUR price: " + historicalPrice.ValueToString();
  //println(message_historicalPrice);

  Wallet BinanceWallet("Binance");
  BinanceWallet.LoadCryptoBalances();

  //println("Setup end");
  //print("\n\n\n");
}

void loop()
{
  WirelessUpdateManager.handle();

  //println("Current Human-readable date/time: " + InternalClock.GetHumanReadableDateTime());
  //println("Current Human-readable date: " + InternalClock.GetCurrentDate());
  //println("Current Human-readable time: " + InternalClock.GetCurrentTime());

  WifiManager.PrintIpAddress();
  delay(1000);

}
