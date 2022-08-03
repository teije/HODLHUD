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
int LOOP_DELAY = 10000;

// Testing WiFi hotspot config
char ssid[]     = "HODL";
char password[] = "HODLHUDV3";
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
  
  //logger->print("Fetching All Wallet Coins");
  //String walletAllCoinsJSON = binanceAPI->execute("/sapi/v1/capital/config/getall");  // Execute API call to fetch all wallet coins
  
  logger->print("Fetching Account Deposits");
  String walletAllDeposits  = binanceAPI->execute("/sapi/v1/capital/deposit/hisrec"); // Execute API call to fetch all deposits to the wallet
  
  logger->print("Fetching Account Snapshot");
  String walletSnapshot  = binanceAPI->execute("/sapi/v1/accountSnapshot", "&type=SPOT"); 

  logger->print("Fetching ADA Trades");
  String adaTrades  = binanceAPI->execute("/api/v3/myTrades", "ADA");
  
  logger->print("Fetching Account Summary");
  String accountSummary = binanceAPI->execute("/api/v3/account");
  
  
  logger->print("Setup end\n\n");
}

void loop() {
  logger->print("Loop start");

  delay(LOOP_DELAY);
  logger->print("Loop end");
}
