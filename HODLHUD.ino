/* TODO 

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
        [ ] Allow connecting/testing sequential WiFi connections
        [ ] Move the WiFi credentials to a file that is not committed to GIT (https://www.arduino.cc/en/Reference/FileRead)
        
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
int LOOP_DELAY = 10000;

// Testing WiFi hotspot config
char ssid[]     = "Deepthought";
char password[] = "dont-forget-your-towel";

Logger* logger = new Logger(" HODLHUD ");

// Instance of the API caller class to fetch data from the binance API
APICaller* binanceAPI = new APICaller("Binance");

void setup() {
  Serial.begin(9600);
  logger->print("Setup start");

  // Test Hotspot WiFi configuration
  WiFiConnector* hotSpotTeije = new WiFiConnector(ssid, password);
  hotSpotTeije->connect();

  // Test Currency Pair
  CurrencyPair* ADAUSD = new CurrencyPair("ADA","EUR", 2.1602);

  // Instance of the API caller class to fetch data from the binance API
  APICaller* binanceAPI = new APICaller("Binance");                                   // Create a new caller for the Binance API
  
  logger->print("Fetching Account Deposits");
  String walletAllDeposits  = binanceAPI->execute("/sapi/v1/capital/deposit/hisrec"); // Execute API call to fetch all deposits to the wallet
  
  logger->print("Fetching Account Snapshot");
  String walletSnapshot  = binanceAPI->execute("/sapi/v1/accountSnapshot", "&type=SPOT"); 
  
  logger->print("Setup end\n\n");
}

void loop() {
  logger->print("Loop start");

  delay(LOOP_DELAY);
  logger->print("Loop end");
}
