// Third party libraries
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <WiFiScan.h>
#include <ETH.h>
#include <WiFiClient.h>
#include <WiFiSTA.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiGeneric.h>

class WiFiConnector {
  private:
    // Properties
    char* ssid;                        // Name of the network
    char* password;                    // Password used to connect to the network
    String deviceHostName;             // Name the device uses to idenify itself on the network/modem
    uint32_t connectionAttemptCount;   // Tracker of current connection attempts
    uint32_t maxConnectionAttempts;    // Amount of times a WiFi connection attempt must be made before the device is reboot
    uint32_t connectionAttemptDelay;   // Time between each connection attempt in ms
    uint32_t notConnectedCounter;      // Time between each connection attempt in ms

  public: 
    WiFiConnector(char* Ssid, char* Password, String DeviceHostName = "HODL-HUD", uint32_t ConnectionAttemptCount = 1, uint32_t MaxConnectionAttempts = 5, uint32_t ConnectionAttemptDelay = 1500) {
      ssid                    = Ssid;
      password                = Password;
      connectionAttemptCount  = ConnectionAttemptCount;
      maxConnectionAttempts   = MaxConnectionAttempts;
      connectionAttemptDelay  = ConnectionAttemptDelay;
    }

    /* Connect to the network using the configured credentials */
    void connect() {
      // Set hostname of the device & connect to the WiFi
      WiFi.hostname(deviceHostName);
      WiFi.begin(ssid, password);
      
      notConnectedCounter = 1;

      while (WiFi.status() != WL_CONNECTED) {
        reconnect();
      }
    }

    
    void reconnect() {
      Serial.println("Reconnecting to WiFi");
      delay(connectionAttemptDelay);
    
      // Reset board if not connected after max attempts
      notConnectedCounter++;
      
      if(notConnectedCounter > maxConnectionAttempts) {
        delay(1000);

        //connect();
        ESP.restart();  // TODO: REBUILD THIS TO RECONNECT WITHOUT REBOOTING OR CREATE A NEW METHOD THAT CAN JUST RECONNECT WITHOUT REBOOTING
      }
    }

    bool isConnectedToWiFi() {
      bool isConnected = WiFi.status() != WL_CONNECTED;

      Serial.println("You are currently ");
      if (isConnected) { Serial.println("NOT ");
      Serial.println("connected to WiFi");
      
      return isConnected;
    }
};
