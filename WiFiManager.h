#ifndef WIFIMANAGER
#define WIFIMANAGER

#include "Base.h"

#include <WiFi.h>

// Define a struct to store the SSID and password for each network
struct NetworkCredentials {
  String ssid;
  String password;
};

class WifiManager: public Base  {
  private:
    NetworkCredentials* networkCredentials;  // Pointer to an array of NetworkCredentials objects
    int networkCount;   // Number of networks in the array
    int maxAttempts;    // Maximum number of connection attempts

    const String toString() override {
      return "WiFiManager.h";
    }
    
  public:
    // Constructor that takes an array of NetworkCredentials objects and the number of networks in the array
    // Optional parameter to set the maximum number of connection attempts
    WifiManager(NetworkCredentials* networkCredentials, int networkCount, int maxAttempts = 5) {
      this->networkCredentials = networkCredentials;
      this->networkCount = networkCount;
      this->maxAttempts = maxAttempts;
    }

    // Method to connect to the networks sequentially
    void connect() {
      println("Connecting to Wi-Fi...");
      int attemptCount = 1;

      // Loop through each network in the array
      for (int i = 0; i < networkCount; i++) {
        println("Target network ");
        print(networkCredentials[i].ssid);

        // Try to connect to the network
        WiFi.begin(networkCredentials[i].ssid.c_str(), networkCredentials[i].password.c_str());

        // Wait for the connection to succeed or the maximum number of attempts to be reached
        while (WiFi.status() != WL_CONNECTED && attemptCount < maxAttempts) {
          delay(1000);
          println("Connecting to WiFi... (" + String(attemptCount) + "/" + String(maxAttempts) + ")");
          attemptCount++;
        }

        // If the connection succeeded, print the network SSID and IP address and break out of the loop
        if (attemptCount != maxAttempts) {
          println("Succesfully connected to: ");
          print(networkCredentials[i].ssid);
          println("Current device IP address: ");
          print(WiFi.localIP().toString());
          break;
        } else {
          // If the connection failed after the maximum number of attempts, print an error message
          println("Unable to connect to ");
          print(networkCredentials[i].ssid);
        }
      }
    }

    // Method to set the maximum number of connection attempts
    void setMaxAttempts(int maxAttempts) {
      this->maxAttempts = maxAttempts;
    }

    // Method to check if there is still a connection to the WiFi network
    bool isConnected() {
      println("WiFi Status: " + WiFi.status());
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
};

#endif // WIFIMANAGER
