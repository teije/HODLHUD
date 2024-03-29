// HODL-HUD Classes
#include "ApiCaller.h"
#include "Base.h"
#include "BinanceApiCaller.h"
#include "CurrencyPair.h"
#include "ESP32Clock.h"
#include "SDManager.h"
#include "JsonParser.h"
#include "Wallet.h"
#include "WiFiManager.h"
#include "WirelessUpdateManager.h"

#include <string>

WiFiManager wifiManager;
ESP32Clock internalClock(wifiManager);
SDManager sdManager;
WirelessUpdateManager wirelessUpdateManager(wifiManager);
BinanceApiCaller binanceApiCaller(wifiManager);

void print(String message);
void println(String message);

int baudrate = 115200;

void setup()
{
  // Set Baudrate
  Serial.begin(baudrate);
  println("Set baudrate for Serial Monitor to: " + baudrate);
  println("Setup start");

  // Configure WiFi Network
  println("Configuring WiFi manager");
  wifiManager.connect();

  // Configure the ability to do wireless updates
  wirelessUpdateManager.begin();
  
  // Create a new instance of the Binance API caller
  println("Configuring Binance API caller");

  // Get the Unix timestamp (for API calls)
  uint32_t unixTime = internalClock.getUnixTimestamp();
  // Get the current time in human-readable format (for UI)
  String timeStr = internalClock.getHumanReadableDateTime();

  // Get the current BTC/EUR price
  CurrencyPair currentPrice = binanceApiCaller.getCurrentPrice("BTC", "EUR");
  String message_currentPrice = "Current BTC/EUR price: " + currentPrice.ValueToString();
  println(message_currentPrice);

  String historicalReadableTime = "2012-09-14 12:00:00";
  uint32_t historicalUnixTime = internalClock.parseHumanReadableTimeToUnix(historicalReadableTime);
  CurrencyPair historicalPrice = binanceApiCaller.getHistoricalPrice("BTC", "EUR", 1646400000000);

  String message_historicalPrice = "Historical BTC/EUR price: " + historicalPrice.ValueToString();
  println(message_historicalPrice);

  Wallet binanceWallet("Binance");
  binanceWallet.LoadCryptoBalances();

  println("Setup end");
  print("\n\n\n");
}

void loop()
{
  wirelessUpdateManager.handle();

  println("Current Human-readable date/time: " + internalClock.getHumanReadableDateTime());
  println("Current Human-readable date: " + internalClock.getCurrentDate());
  println("Current Human-readable time: " + internalClock.getCurrentTime());

  wifiManager.printIpAddress();
  delay(1000);

}

/*
   Shorthand method to print the provided message to the serial monitor
   Starts the message on the same line as the previous message
*/
void print(String message) 
{
  Serial.print(message);
}
/*
   Shorthand method to print the provided message to the serial monitor
   Starts the message on a newline
*/
void println(String message) 
{
  Serial.print("\n[HOLDHUD]                      " + message);
}
