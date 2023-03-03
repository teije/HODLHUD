#ifndef WIRELESSUPDATEMANAGER
#define WIRELESSUPDATEMANAGER

#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include "WifiManager.h"

class WirelessUpdateManager : public Base  {
  public:
    WirelessUpdateManager(WifiManager wifiManager): wifiManager(wifiManager) 
    {
      
    }
  
    void configure(const char* devicename, const char* devicePassword) {
      wifiManager.ensureConnection();

      // Set up OTA
      println("Configuring the ability to run Wireless Updates");
      ArduinoOTA.setHostname(devicename);
      ArduinoOTA.setPassword(devicePassword);
      ArduinoOTA.begin();
    }

    void handle() {
      println("Processing Wireless Update");
      ArduinoOTA.handle();
    }

  private:
    WifiManager wifiManager;

    String Type() {
      return "WirelessUpdateManager.h";
    }
};

#endif
