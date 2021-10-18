/* TODO 

[ ] We want to: Consistently log code results/status during operation
    [X] For this we need to: Create Logger class
        And that requires the following:
        [ ] Create properties
            [ ] 
        [X] Create functions
            [X]  Print
    [ ] Initialize & call logger class from each other class
        [X] HODLHUD Main File
        [X] WiFi Connector class
        [X] Currency pair data class
        [ ] API caller class
        [ ] UI element data class
        [ ] Display printer class

[X] We want to: Connect to WiFi
    [X] Create WiFi connector class
        [X] Create properties
            [X] SSID:     string
            [X] Password: string
        [ ] Create functions
            [X] Connect()     return boolean:connectionSuccesful
            [X] Reconnect()   return boolean:connectionSuccesful
            [ ] IsConnected() return boolean:isConnected
        [X] Initialize WiFi connector class
        [X] Establish a WiFi connection
        [ ] Allow the connection/testing multiple WiFi connections
        [ ] Move the WiFi credentials to a file that is not committed to GIT (https://www.arduino.cc/en/Reference/FileRead)
        
[ ] We want to: Fetch and store data (from the Binance API)
    [X] Create a way to hold currency data
        [X] Create a CurrencyPair class/object 
            [X] Create properties
                [X] Main Currency:    string     
                [X] Cointer Currency: string
                [X] Spot Price:       float
            [ ] Create functions
                [ ]     
            
    [ ] Make an API call to Binance
        [X] Create Binance API service class
            [ ] Create properties
                [X] Name:     string
                [X] Base URL: string
                [X] API Key:  string
            [ ] Create functions
                [ ] getWalletContents()                           return JSON string
                [ ] getSpotPrice(dateTime=default:now)            return JSON string
                [ ] getPriceForPeriod(startDateTime, endDateTime) return JSON string
                [ ]
            [ ] Read API key from file
            [ ] Construct an API call
                [ ] Provide a signature: https://techtutorialsx.com/2018/01/25/esp32-arduino-applying-the-hmac-sha-256-mechanism/
                [X] Provide an api-key
                [ ] Provide an api-secret
                [X] Provide the milliseconds http://kendziorra.nl/arduino/114-my-simple-milliseconds-time-library

[ ] We want to: Print visual elements to the display
    [ ] Create a UIElement data object
        [ ] Create properties
            [ ] Name:         string
            [ ] Shape Type:   string     
            [ ] Start Pos X:  int 
            [ ] Start Pos Y:  int
            [ ] Width (X):    int
            [ ] Width (Y):    int
            [ ] Colour/Shade: int/string
        [ ] Create functions
            [ ]     
    
    [ ] Create a Display printer class (that prints UIElements)
        [ ] Create properties
                [ ]  
            [ ] Create functions
                [ ] DisplayElement(UIElement)
                [ ] Reset Display Fully()
                [ ] Reset Display Partially()
                [ ] 

[ ] We want to: Interact with the elements on the display
    [ ] 
    
*/  

#include <HTTPClient.h>
#include <ArduinoJson.h>


// Project classes
#include "Logger.h"
#include "WiFiConnector.h"
#include "CurrencyPair.h"
#include "APICaller.h"

// Constants
int LOOP_DELAY = 5000;

// Testing WiFi hotspot config
const char* ssid     = "HODL";
const char* password = "HODLHUDV3";

Logger* logger = new Logger(" HODLHUD ");

// Instance of the API caller class to fetch data from the binance API
APICaller* binanceAPI = new APICaller("Binance");

void setup() {
  Serial.begin(9600);
  logger->print("Setup start");

  // Test Hotspot WiFi configuration
  WiFiConnector* hotSpotTeije = new WiFiConnector("HODL", "HODLHUDV3");
  hotSpotTeije->connect();

  // Test Currency Pair
  CurrencyPair* ADAUSD = new CurrencyPair("ADA","EUR", 2.1602);

  // Instance of the API caller class to fetch data from the binance API
  APICaller* binanceAPI = new APICaller("Binance");         // Create a new caller for the Binance API
  String timestamp = binanceAPI->timestamp();               // Fetch the current timestamp
  const char* payload = ("timestamp=" + timestamp).c_str(); // Construct the payload for the signature
  String signature = binanceAPI->signature(payload);        // Create a signature from the payload

  String response = binanceAPI->execute("/sapi/v1/capital/config/getall?timestamp=" + timestamp + "&signature=" + signature); // Execute the API call to fetch wallet contents

  logger->print(response);

  String deposit_timestamp = binanceAPI->timestamp();               // Fetch the current timestamp
  const char* deposit_payload = ("timestamp=" + deposit_timestamp).c_str(); // Construct the payload for the signature
  String deposit_signature = binanceAPI->signature(deposit_payload);        // Create a signature from the payload

  String depositResponse = binanceAPI->execute("/sapi/v1/capital/deposit/hisrec?timestamp=" + deposit_timestamp + "&signature=" + deposit_signature);
  
  logger->print(depositResponse);

  logger->print("Setup end");
}

void loop() {
  logger->print("Loop start");
  
  delay(LOOP_DELAY);
  logger->print("Look end");
}
