// HODL-HUD Classes
#include "ApiCaller.h"
#include "Base.h"
#include "BinanceApiCaller.h"
#include "BinanceManager.h"
#include "CurrencyPair.h"
#include "ESP32Clock.h"
#include "SDManager.h"
#include <string.h>
#include "JsonParser.h"
#include "Wallet.h"
#include "WiFiManager.h"
#include "WirelessDebuggingManager.h"
#include "WirelessUpdateManager.h"

WiFiManager wifiManager;
ESP32Clock internalClock(wifiManager);
SDManager sdManager;

String toString();

WirelessUpdateManager wirelessUpdateManager(wifiManager);
BinanceApiCaller binanceApiCaller(wifiManager);
WirelessDebuggingManager wirelessDebuggingManager(wifiManager);

void setup()
{
  Serial.begin(115200);
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
  String message_currentPrice = "Current BTC/EUR price: " + currentPrice.value;
  println(message_currentPrice);

  String historicalReadableTime = "2012-09-14 12:00:00";
  uint32_t historicalUnixTime = internalClock.parseHumanReadableTimeToUnix(historicalReadableTime);
  CurrencyPair historicalPrice = binanceApiCaller.getHistoricalPrice("BTC", "EUR", 1646400000000);

  //const char * message_historicalPrice = "Historical BTC/EUR price: " + historicalPrice.value;
  //println(message_historicalPrice);

  Wallet wallet("Binance");

  println("Setup end");
  print("\n\n\n");
}

void loop()
{
  wirelessUpdateManager.handle();
  internalClock.getHumanReadableDateTime();
  wirelessDebuggingManager.
  wifiManager.printIpAddress();

  // CurrencyPair currentPrice = binanceApiCaller.getCurrentPrice("BTC", "EUR");
  // String message_currentPrice = "Current BTC/EUR price: " + currentPrice.value;
  // println(message_currentPrice);
  
  
  delay(1000);
}

/*
   Since the main .ino file cannot inherit the Base class it has its own set of logging methods
*/
String Type() 
{
  return "HODLHUD";
}
void print(String message) 
{
  Serial.print(message);
}
void println(String message) 
{
  Serial.println("\n[HOLDHUD]                      " + message);
}

const char * convertFloatToCharArray(float value, int ARRAY_LENGTH)
{
  char result[ARRAY_LENGTH];
  dtostrf(value, ARRAY_LENGTH, 3, result);
  return result;
}
