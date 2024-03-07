#ifndef WIFIMANAGER
#define WIFIMANAGER

#include "Base.h"
#include "SettingsManager.h"

#include <WiFi.h>

class WiFiManager: public Base  {
  public:
    // Constructor that takes an array of NetworkCredentials objects and the number of networks in the array
    // Optional parameter to set the maximum number of connection attempts
    WiFiManager() {
      this->networkCredentials = SettingsManager::NetworkCredentialList;
      this->networkCount = SettingsManager::NetworkCredentialsCount;
      this->maxAttempts = 5;
    }

    void connect() {
        println("Connecting to Wi-Fi", "configure");
        println("Stored network SSIDs:");
    
        // Loop through stored network credentials and print their SSIDs
        for (int i = 0; i < networkCount; i++) {
            println("- ");
            print(networkCredentials[i].Ssid);
        }
        
        // Scan for available networks
        println("Scanning for available networks");
        int numNetworks = WiFi.scanNetworks();
        if (numNetworks == 0) {
            println("No networks found.");
            return;
        }
    
        // Flag to check if any of the stored networks are visible
        bool networkFound = false;
    
        // Loop through each network in the array
        for (int i = 0; i < networkCount; i++) {
            // Check if stored network is visible
            for (int j = 0; j < numNetworks; j++) {
                if (networkCredentials[i].Ssid.equals(WiFi.SSID(j))) {
                    networkFound = true;
                    break;
                }
            }
    
            if (networkFound) {
                println("Target network ");
                print(networkCredentials[i].Name + " (" + networkCredentials[i].Ssid + ")");
                // Try to connect to the network
                WiFi.begin(networkCredentials[i].Ssid.c_str(), networkCredentials[i].Password.c_str());
    
                int attemptCount = 1;
                // Wait for the connection to succeed or the maximum number of attempts to be reached
    
                println("Establishing WiFi connection");
                while (WiFi.status() != WL_CONNECTED && attemptCount <= maxAttempts) {
                    delay(1000);
                    //println("Connecting to WiFi... (" + String(attemptCount) + "/" + String(maxAttempts) + ")");
    
                    print(".");
    
                    attemptCount++;
                }
    
                // If the connection succeeded, print the network SSID and IP address and return from the function
                if (WiFi.status() == WL_CONNECTED) {
                    println("Successfully connected to: ");
                    this->connectedNetworkSsid = networkCredentials[i].Ssid;
                    print(networkCredentials[i].Name + " (" + connectedNetworkSsid + ")");
                    println("Current device IP address: ");
                    print(WiFi.localIP().toString());
                    return;
                } else {
                    // If the connection failed after the maximum number of attempts, print an error message
                    println("Unable to connect to ", "warning");
                    print(networkCredentials[i].Ssid);
                }
            }
        }
    
        // If none of the stored networks are visible
        if (!networkFound) {
            println("None of the stored networks are visible to the device");
        }
    
        // If all attempts fail, wait for some time before retrying to connect
        delay(1000);
    
        // Recursively call the connect() function to try again to connect to any stored wifi network 
        connect();
    }

    // Function to scan for available WiFi networks and print the SSIDs
    void scan() {
      // Scan for available networks
      int numNetworks = WiFi.scanNetworks();
      if (numNetworks == 0) {
        println("No networks found.");
      } else {
        println (numNetworks);
        print(" networks found:");
        for (int i = 0; i < numNetworks; ++i) {
          println("- ");
          print(WiFi.SSID(i)); // Print the SSID (name) of the network
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
      println("Ensuring WiFi connection...", "configure");
      if (!isConnected()) {
        println("Connection lost. Reconnecting...");
        connect();
      }

      println("Connection OK! (" + connectedNetworkSsid + ")");
    }

    void printIpAddress()
    {
      println("Current device IP address: ", "configure");
      print(WiFi.localIP().toString());
    }
    
  private:
    NetworkCredentials* networkCredentials;  // An array of NetworkCredentials objects
    SettingsManager settingsManager;
    int networkCount;                        // Number of networks in the array
    int maxAttempts;                         // Maximum number of connection attempts
    String connectedNetworkSsid;             // Name of the currently connected network

    String Type() {
      return "WiFiManager.h";
    }
};

#endif // WIFIMANAGER
