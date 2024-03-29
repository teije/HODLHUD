#ifndef SETTINGSMANAGER
#define SETTINGSMANAGER

#include <Arduino.h>
#include <string>

// Struct to store network credentials
struct NetworkCredentials {
  String Name;      // Name of the network
  String Ssid;      // SSID of the network
  String Password;  // Password of the network
};

// Struct to store API credentials
struct ApiCredentials {
  String Name;        // Name of the API
  String ApiKey;      // API key to access the API
  String ApiKeyLabel; // Label of the API key
  String ApiUrl;      // URL of the API
};
/*
 * This settings manager class exists to hold hard-coded values 
 * until we get the SD-card up and running
 */
class SettingsManager {
  public:
    static NetworkCredentials GetNetworkCredentialByName(String name) {
      for (int i = 0; i < NetworkCredentialsCount; i++) {
        if (name == NetworkCredentialList[i].Name) {
          return NetworkCredentialList[i];
        }
      }
      // If the credential was not found, return an empty struct
      return NetworkCredentials();
    }

    // Get a specific API credential by name
    static ApiCredentials GetApiCredentialByName(String name) {
      for (int i = 0; i < ApiCredentialsCount; i++) {
        if (name == ApiCredentialList[i].Name) {
          return ApiCredentialList[i];
        }
      }
      // If the credential was not found, return an empty struct
      return ApiCredentials();
    }
  
    /*
     * WARNING! The count integer and the value in between the [] must be equal!!!
     */
    static int NetworkCredentialsCount;
    static NetworkCredentials NetworkCredentialList[4];

    /*
     * WARNING! The count integer and the value in between the [] must be equal!!!
     */
    static int ApiCredentialsCount;
    static ApiCredentials ApiCredentialList[1];
};

int SettingsManager::NetworkCredentialsCount = 4;
int SettingsManager::ApiCredentialsCount = 1;

NetworkCredentials SettingsManager::NetworkCredentialList[4] = 
{
  {"WiFi - Pap & Mam", "Ziggo12857", "EmmaDeBeatl3!"},
  {"WiFi - Pap & Mam [5GHz]", "Ziggo12857 5GHz", "EmmaDeBeatl3!"},
  {"WiFi Hotspot - Telefoon Teije", "Deepthought", "dont-forget-your-towel"},
  {"WiFi - Guest T&N", "KPNF8A4B6_GUEST", "937K6Pj14Z1tJn1T"},
};

ApiCredentials SettingsManager::ApiCredentialList[1] = 
{
  { "Binance", "X-MBX-APIKEY", "QD9otAMisbjmuOfccmiltNINByzDzpQRjpFQOKjlzP8Xw4rqwdvbTbfnD2FClXh8", "https://api.binance.com" }
};

#endif
