// HODL-HUD Classes
#include "ApiCaller.h"
#include "Base.h"
#include "BinanceApiCaller.h"
#include "CurrencyPair.h"
#include "JsonParser.h"
#include "InternalClock.h"
#include "WiFiManager.h"

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

  println("Constructing network manager");
  int networkCount = 1;
  WifiManager wifiManager(networks, networkCount);

  // Set the internal clock of the ESP32 (so time based data is accurate)
  println("Configuring internal clock");
  InternalClock internalClock(wifiManager);
  internalClock.setClock();

  // Define the Binance API credentials
  ApiCredentials binanceCredentials = {
    "Binance",
    "X-MBX-APIKEY",
    "QD9otAMisbjmuOfccmiltNINByzDzpQRjpFQOKjlzP8Xw4rqwdvbTbfnD2FClXh8",
    "https://api.binance.com"
  };

  // Create a new instance of the Binance API caller
  BinanceApiCaller binanceApiCaller(binanceCredentials, wifiManager);
  
  // Get the current BTC/EUR price
  CurrencyPair pairCurrentPrice = binanceApiCaller.getCurrencyPair("BTC", "EUR");
  println("Current BTC/EUR price: " + pairCurrentPrice.toString());

  println("Setup end");
}

void loop()
{

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
