#include "Base.h"
#include "WiFiManager.h"
#include "APICaller.h"

void setup()
{
  Serial.begin(115200);
  println("Setup start");

  // Configure WiFi Networks
  NetworkCredentials networks[] = {
    {"KPNF8A4B6", "93bwMf2vsqdsVJcx"}
  };

  int networkCount = 1;
  WifiManager wifiManager(networks, networkCount);
  wifiManager.connect();

  // Define the Binance API credentials
  ApiCredentials binanceCredentials = {
    "Binance",
    "X-MBX-APIKEY",
    "QD9otAMisbjmuOfccmiltNINByzDzpQRjpFQOKjlzP8Xw4rqwdvbTbfnD2FClXh8",
    "https://api.binance.com"
  };

  // Create an instance of the ApiManager with the Binance API credentials
  ApiCaller binanceApi(binanceCredentials, wifiManager);

  // Call the Binance API to get the BTC/EUR value
  String response = binanceApi.GET("/api/v3/ticker/price?symbol=BTCEUR");

  println("Setup end");
}

void loop()
{

}

const String toString() {
  return "HODLHUD.h";
}
void print(String message) {
  Serial.print(message);
}
void println(String message) {
  Serial.print("\n[" + toString() + "] " + message);
}
