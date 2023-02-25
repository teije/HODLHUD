// HODL-HUD Classes
#include "ApiCaller.h"
#include "Base.h"
#include "BinanceApiCaller.h"
#include "CurrencyPair.h"
#include "JsonParser.h"
#include "WiFiManager.h"

// Internal Clock
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* ntp_server = "pool.ntp.org";

// Internal Clock
WiFiUDP ntp_udp;
NTPClient ntp_client(ntp_udp, ntp_server);

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

  // Internal Clock
  println("Configuring internal clock");
  ntp_client.begin();
  ntp_client.setTimeOffset(3600); // Set timezone offset to UTC+1

  // Define the Binance API credentials
  println("Configuring API credentials");
  ApiCredentials binanceCredentials = {
    "Binance",
    "X-MBX-APIKEY",
    "QD9otAMisbjmuOfccmiltNINByzDzpQRjpFQOKjlzP8Xw4rqwdvbTbfnD2FClXh8",
    "https://api.binance.com"
  };

  // Create a new instance of the Binance API caller
  println("Configuring API credentials");
  BinanceApiCaller binanceApiCaller(binanceCredentials, wifiManager);

  // Get the current BTC/EUR price
  CurrencyPair pairCurrentPrice = binanceApiCaller.getCurrencyPair("BTC", "EUR");
  println("Current BTC/EUR price: " + pairCurrentPrice.toString());

  println("Setup end");
}

void loop()
{
  // Internal Clock
  ntp_client.update();
  time_t current_time = ntp_client.getEpochTime();
  struct tm timeinfo;
  gmtime_r(&current_time, &timeinfo);
  Serial.printf("Current time: %02d:%02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

  delay(1000);
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
