#ifndef WIFIMANAGER
#define WIFIMANAGER

#include "SettingsManager.h"

#include <WiFi.h>

class WiFiManager {
  public:
    String connectedNetworkSsid;             // Name of the currently connected network
    
    // Constructor that takes an array of NetworkCredentials objects and the number of networks in the array
    // Optional parameter to set the maximum number of connection attempts
    WiFiManager() {
      this->networkCredentials = settingsManager.NetworkCredentialList;
      this->networkCount = settingsManager.NetworkCredentialsCount;
      this->maxConnectionAttempts = 5;
    }

    // Method to connect to the networks sequentially
    void Connect() {
      //println("Connecting to Wi-Fi", "configure");
      
      // Loop through each network in the array
      for (int i = 0; i < networkCount; i++) {
        //println("Target network ");
        //print(NetworkCredentials[i].Name + " (" + NetworkCredentials[i].Ssid + ")");
    
        // Try to connect to the network
        WiFi.begin(networkCredentials[i].Ssid.c_str(), networkCredentials[i].Password.c_str());
        
        int attemptCount = 1;
        // Wait for the connection to succeed or the maximum number of attempts to be reached
        //println("Establishing WiFi connection");
        while (WiFi.status() != WL_CONNECTED && attemptCount <= maxConnectionAttempts) {
          delay(1000);
          //println("Connecting to WiFi... (" + String(attemptCount) + "/" + String(maxAttempts) + ")");

          //print(".");
          
          attemptCount++;
        }
    
        // If the connection succeeded, print the network SSID and IP address and return from the function
        if (WiFi.status() == WL_CONNECTED) {
          //println("Successfully connected to: ");
          this->connectedNetworkSsid = networkCredentials[i].Ssid;
          //print(NetworkCredentials[i].Name + " (" + connectedNetworkSsid + ")");
          //println("Current device IP address: ");
          //print(WiFi.localIP().toString());
          return;
        } else {
          // If the connection failed after the maximum number of attempts, print an error message
          //println("Unable to connect to ", "warning");
          //print(NetworkCredentials[i].Ssid);
        }
      }
      
      // If all attempts fail, wait for some time before retrying
      delay(1000);
      
      // Recursively call the Connect() function to try again
      Connect();
    }


    // Method to set the maximum number of connection attempts
    void SetMaxAttempts(int maxAttempts) {
      this->maxConnectionAttempts = maxAttempts;
    }

    // Method to check if there is still a connection to the WiFi network
    bool IsConnected() {
      return (WiFi.status() == WL_CONNECTED);
    }

    void EnsureConnection() {
      //println("Ensuring WiFi connection...", "configure");
      if (!IsConnected()) {
        //println("Connection lost. Reconnecting...");
        Connect();
      }

      //println("Connection OK! (" + connectedNetworkSsid + ")");
    }

    void PrintIpAddress()
    {
      //println("Current device IP address: ", "configure");
      //print(WiFi.localIP().toString());
    }
    
  private:
    NetworkCredentials* networkCredentials;  // An array of NetworkCredentials objects
    SettingsManager settingsManager;  
    int networkCount;                        // Number of networks in the array
    int maxConnectionAttempts;               // Maximum number of connection attempts
};

#endif // WIFIMANAGER
