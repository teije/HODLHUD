// HODL-HUD Classes
#include "ApiCaller.h"
#include "Base.h"
#include "BinanceApiCaller.h"
#include "CurrencyPair.h"
#include "JsonParser.h"
#include "WiFiManager.h"

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* ntp_server = "pool.ntp.org";

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

  // Get the current BTC/EUR price
  CurrencyPair pairCurrentPrice = binanceApiCaller.getCurrentPrice("BTC", "EUR");
  println("Current BTC/EUR price: " + String(pairCurrentPrice.getValue()));

  println("Setup end");
  print("\n\n\n\n\n");
}

void loop()
{
  println("Loop start");
  


  delay(1000);
  println("Loop end");
}

String toString() {
  return "HODLHUD.h";
}
void print(String message) {
  Serial.print(message);
}
void println(String message) {
  Serial.print("\n[" + toString() + "] " + message);
}
