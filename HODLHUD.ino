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

WifiManager wifiManager;
ESP32Clock internalClock(wifiManager);

// Settings for the SD card
const int chipSelectPin = 27;
SDManager sdManager(chipSelectPin);

String toString();
void print(String message);
void println(String message);

void setup()
{
  Serial.begin(115200);
  println("Setup start");

  // Configure WiFi Network
  println("Configuring WiFi manager");
  wifiManager.connect();

  // Configure the ability to do wireless updates
  WirelessUpdateManager wirelessUpdateManager(wifiManager);
  wirelessUpdateManager.configure("HODL-HUD", "123");

  // Create a new instance of the Binance API caller
  println("Configuring Binance API caller");
  BinanceApiCaller binanceApiCaller(wifiManager); 

  // Get the Unix timestamp (for API calls)
  uint32_t unixTime = internalClock.getUnixTimestamp();
  // Get the current time in human-readable format (for UI)
  String timeStr = internalClock.getHumanReadableTime();

  // Get the current BTC/EUR price
  CurrencyPair currentPrice = binanceApiCaller.getCurrentPrice("BTC", "EUR");
  println("Current BTC/EUR price: " + String(currentPrice.value));

  String historicalReadableTime = "2012-09-14 12:00:00";
  uint32_t historicalUnixTime = internalClock.parseHumanReadableTimeToUnix(historicalReadableTime);
  CurrencyPair historicalPrice = binanceApiCaller.getHistoricalPrice("BTC", "EUR", 1646400000000);
  println("Historical BTC/EUR price: " + String(historicalPrice.value));

  Wallet wallet("Binance");

  // Initialize SD card
  if (!sdManager.begin()) {
    return;
  }

  // Write data to a file on the SD card.
  sdManager.write("helloworld.txt", "Hello, world!");

  // Read data from a file on the SD card.
  println(sdManager.read("helloworld.txt"));

  // Delete a file from the SD card.
  sdManager.remove("helloworld.txt");

  println("Setup end");
  print("\n\n\n");
}

void loop()
{  
  internalClock.getHumanReadableTime();

  delay(1000);
}

/*
 * Since the main .ino file cannot inherit the Base class it has its own set of logging methods
 */
String Type() {
  return "HODLHUD";
}
void print(String message) {
  Serial.print(message);
}
void println(String message) {
  String prefix = "\n[" + Type() + "]                      ";
  Serial.print(prefix + message);
}
