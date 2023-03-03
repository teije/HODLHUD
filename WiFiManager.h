#ifndef WIFIMANAGER
#define WIFIMANAGER

#include "Base.h"
#include "SettingsManager.h"

#include <WiFi.h>

class WifiManager: public Base  {
  public:
    // Constructor that takes an array of NetworkCredentials objects and the number of networks in the array
    // Optional parameter to set the maximum number of connection attempts
    WifiManager() {
      this->networkCredentials = SettingsManager::NetworkCredentialList;
      this->networkCount = SettingsManager::NetworkCredentialsCount;
      this->maxAttempts = 5;
    }

    // Method to connect to the networks sequentially
    void connect() {
      println("Connecting to Wi-Fi...");
      int attemptCount = 1;

      // Loop through each network in the array
      for (int i = 0; i < networkCount; i++) {
        println("Target network ");
        print(networkCredentials[i].Ssid);

        // Try to connect to the network
        WiFi.begin(networkCredentials[i].Ssid.c_str(), networkCredentials[i].Password.c_str());

        // Wait for the connection to succeed or the maximum number of attempts to be reached
        while (WiFi.status() != WL_CONNECTED && attemptCount < maxAttempts) {
          delay(1000);
          println("Connecting to WiFi... (" + String(attemptCount) + "/" + String(maxAttempts) + ")");
          attemptCount++;
        }

        // If the connection succeeded, print the network SSID and IP address and break out of the loop
        if (attemptCount != maxAttempts) {
          println("Succesfully connected to: ");
          print(networkCredentials[i].Ssid);
          println("Current device IP address: ");
          print(WiFi.localIP().toString());
          break;
        } else {
          // If the connection failed after the maximum number of attempts, print an error message
          println("Unable to connect to ");
          print(networkCredentials[i].Ssid);
        }
      }
    }

    // Method to set the maximum number of connection attempts
    void setMaxAttempts(int maxAttempts) {
      this->maxAttempts = maxAttempts;
    }

    // Method to check if there is still a connection to the WiFi network
    bool isConnected() {
      return (WiFi.status() == WL_CONNECTED);
    }

    void ensureConnection() {
      println("Ensuring WiFi connection...");
      if (!isConnected()) {
        println("Connection lost. Reconnecting...");
        connect();
      }

      println("Connection OK!");
    }
    
  private:
    NetworkCredentials* networkCredentials;  // An array of NetworkCredentials objects
    SettingsManager settingsManager;
    int networkCount;   // Number of networks in the array
    int maxAttempts;    // Maximum number of connection attempts

    String Type() {
      return "WiFiManager.h";
    }
};

#endif // WIFIMANAGER
