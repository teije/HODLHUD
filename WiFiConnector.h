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
    String deviceHostName;              // Name the device uses to idenify itself on the network/modem
    uint32_t connectionAttemptCount;    // Tracker of current connection attempts
    uint32_t maxConnectionAttempts;     // Amount of times a WiFi connection attempt must be made before the device is reboot
    uint32_t connectionAttemptDelay;    // Time between each connection attempt in ms
    uint32_t notConnectedCounter;    // Time between each connection attempt in ms

    // Services
    Logger *_logger;

  public: 
    WiFiConnector(char* Ssid, char* Password, String DeviceHostName = "HODL-HUD", uint32_t ConnectionAttemptCount = 1, uint32_t MaxConnectionAttempts = 5, uint32_t ConnectionAttemptDelay = 2500) {
      _logger                 = new Logger();
      
      ssid                    = Ssid;
      password                = Password;
      connectionAttemptCount  = ConnectionAttemptCount;
      maxConnectionAttempts   = MaxConnectionAttempts;
      connectionAttemptDelay  = ConnectionAttemptDelay;

      _logger->setSourceName("WiFiConnector");
      _logger->print("New WiFi connection configured: " + String(ssid) + "");
    }

    /* Connect to the network using the configured credentials */
    void connect() {
      // Set hostname of the device & connect to the WiFi
      WiFi.hostname(deviceHostName);
      WiFi.begin(ssid, password);
      
      _logger->print("Connecting to WiFi (" + String(ssid) + ")");
      _logger->print("Using MAC address: " + WiFi.macAddress());

      notConnectedCounter = 1;

      while (WiFi.status() != WL_CONNECTED) {
        reconnect();
      }

      _logger->print("WiFi connected");
    }

    
    void reconnect() {
      delay(connectionAttemptDelay);
      
      // Report how many times a connection has been attempted
      _logger->print("Connection attempt " + String(notConnectedCounter) + "/" + String(maxConnectionAttempts));
    
      // Reset board if not connected after max attempts
      notConnectedCounter++;
      
      if(notConnectedCounter > maxConnectionAttempts) {
        _logger->print("Resetting " + deviceHostName + " due to Wifi not connecting...");
        _logger->print("Is your mobile hotspot, WiFi or ssid/password setup correctly & online?");
        
        delay(1000);
        
        ESP.restart();
      }
    }
};
