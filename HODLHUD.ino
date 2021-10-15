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
        [ ] Create Binance API service class
            [ ] Create properties
                [ ] Name:     string
                [ ] Base URL: string
                [ ] API Key:  string
            [ ] Create functions
                [ ] getWalletContents()                           return JSON string
                [ ] getSpotPrice(dateTime=default:now)            return JSON string
                [ ] getPriceForPeriod(startDateTime, endDateTime) return JSON string
                [ ]

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

// Third party libraries
#include <Ethernet.h>
#include <HTTPClient.h>
#include <WiFi.h>

// Project classes
#include "Logger.h"
#include "WiFiConnector.h"
#include "CurrencyPair.h"

// Constants
int LOOP_DELAY = 1000;

// Testing WiFi hotspot config
const char* ssid     = "HODL";
const char* password = "HODLHUDV3";

Logger* LOGGER = new Logger("HODLHUD");

void setup() {
  Serial.begin(9600);
  LOGGER->print("Setup start");

  WiFiConnector* hotSpotTeije = new WiFiConnector("HODL", "HODLHUDV3");

  CurrencyPair* ADAUSD = new CurrencyPair("ADA","EUR", 2.1602);

  LOGGER->print("Setup end");
}

void loop() {
  LOGGER->print("Loop start");
  
  
  delay(LOOP_DELAY);
  LOGGER->print("Look end");
}
