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

[ ] We want to: Fetch all available coins from a Google Sheet
    [ ] Create the google sheet document
    [ ] We want to store:
        [ ] A trades per row, with values:
            [ ] Base symbol
            [ ] Counter symbol
            [ ] Amount
            [ ] Date/Time
        [ ] A row (seperate sheet?) that holds our balance for each coin with amount > 0
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

#include <HTTPClient.h>
#include <ArduinoJson.h>


// Project classes
#include "Logger.h"
#include "WiFiConnector.h"
#include "Coin.h"
#include "ApiCaller.h"

// Constants
int LOOP_DELAY = 10000;

// Testing WiFi hotspot config
char ssid[]     = "Deepthought";
char password[] = "dont-forget-your-towel";

Logger* logger = new Logger(" HODLHUD ");

void setup() {
  Serial.begin(9600);
  logger->print("Setup start");

  // Test Hotspot WiFi configuration
  WiFiConnector* hotSpotTeije = new WiFiConnector(ssid, password);
  hotSpotTeije->connect();

  // Test Coins
  Coin* ADA = new Coin("ADA", "Cardano");
  Coin* ADAwithAmount = new Coin("ADA", "Cardano", 10, 1.50);

  
  ApiCaller* apiCaller = new ApiCaller(); // Instance of the API caller class to fetch data from the binance API

  logger->print("Fetching Account Snapshot");
  String walletSnapshot  = apiCaller->executeBinance("/sapi/v1/accountSnapshot", "&type=SPOT", true); 

  logger->print("Fetching ADA/EUR Spot Price");
  String adaSpotPrice = apiCaller->executeBinance("/api/v3/ticker/price", "?symbol=" + ADA->symbol + "USDT", false);

  apiCaller->getUSDtoEURrate();
  apiCaller->getEURtoUSDrate();

  logger->print("The 'trades' Google Sheet Page - Range A1:B2");
  apiCaller->executeGoogle("trades", "A1", "B2");
  
  logger->print("The 'balance' Google Sheet Page - Range A1:B2");
  apiCaller->executeGoogle("balance", "A1", "B2");
 
  logger->print("Setup end\n\n");
}

void loop() {
  logger->print("Loop start");

  delay(LOOP_DELAY);
  logger->print("Loop end");
}
