// HODL-HUD Classes
#include "ApiCaller.h"
#include "Base.h"
#include "BinanceApiCaller.h"
#include "CurrencyPair.h"
#include "ESP32Clock.h"
#include "JsonParser.h"
#include "WiFiManager.h"
#include "WirelessUpdateManager.h"

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* ntp_server = "pool.ntp.org";

// Internal clock
ESP32Clock internalClock;

String toString();
void print(String message);
void println(String message);

void setup()
{
  Serial.begin(115200);
  println("Setup start");

  // Configure WiFi Networks
  println("Configuring network credentials");
  NetworkCredentials networks[] = {
    {"KPNF8A4B6", "93bwMf2vsqdsVJcx"}
  };

  println("Configuring WiFi manager");
  int networkCount = 1;
  WifiManager wifiManager(networks, networkCount);
  wifiManager.connect();

  // Configure the ability to do wireless updates
  WirelessUpdateManager wirelessUpdateManager(wifiManager);
  wirelessUpdateManager.configure("HODL-HUD", "dont-forget-your-towel");

  // Define the Binance API credentials
  println("Configuring API credentials");
  ApiCredentials binanceCredentials = {
    "Binance",
    "X-MBX-APIKEY",
    "QD9otAMisbjmuOfccmiltNINByzDzpQRjpFQOKjlzP8Xw4rqwdvbTbfnD2FClXh8",
    "https://api.binance.com"
  };

  // Create a new instance of the Binance API caller
  println("Configuring Binance API caller");
  BinanceApiCaller binanceApiCaller(binanceCredentials, wifiManager); 

  // Get the Unix timestamp (for API calls)
  uint32_t unixTime = internalClock.getUnixTimestamp();
  // Get the current time in human-readable format (for UI)
  String timeStr = internalClock.getHumanReadableTime();

  // Get the current BTC/EUR price
  CurrencyPair pairCurrentPrice = binanceApiCaller.getCurrentPrice("BTC", "EUR");
  println("Current BTC/EUR price: " + String(pairCurrentPrice.value));

  println("Setup end");
  print("\n\n\n\n\n");
}

void loop()
{
  //println("Loop start");
  
  internalClock.getHumanReadableTime();

  delay(1000);
  //println("Loop end");
}

String Type() {
  return "HODLHUD";
}
void print(String message) {
  Serial.print(message);
}
void println(String message) {
  Serial.print("\n[" + Type() + "] " + message);
}
