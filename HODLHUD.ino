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
    [X] Create the google sheet document
    [ ] We want to store:
        [X] A trades per row, with values:
            [X] Base symbol
            [X] Counter symbol
            [X] Amount
            [X] Date/Time
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

// External Libraries
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Project classes
#include "Logger.h"
#include "WiFiConnector.h"
#include "Coin.h"
#include "ApiCaller.h"
#include "TransactionService.h"

// Constants
int LOOP_DELAY = 10000;

// Testing WiFi hotspot config
char ssid[]     = "Deepthought";
char password[] = "dont-forget-your-towel";

Logger *logger = new Logger("HODLHUD");

void setup() {
  Serial.begin(9600);
  logger->println("Setup start");

  // Test Hotspot WiFi configuration
  WiFiConnector* hotSpotTeije = new WiFiConnector(ssid, password);
  hotSpotTeije->connect();

  logger->println("Setup end\n\n");
}

  Logger *logger = new Logger("HODLHUD");
void loop() {  
  logger->println("Loop start");
  

  // Grab all transactions in the Google Sheet
  TransactionService *transactionService = new TransactionService(apiCaller);
  
  int transactionCount = transactionService->getTransactionCount();
  Transaction *transactions = transactionService->getTransactions();
  //CoinService *coinService = new CoinService(apiCaller);

  // Grab all values for all transactions
  String symbols[sizeof(transactions)];
  
  for(int i=0; i<sizeof(transactions); i++) {
    Transaction t = transactions[i];
    Coin *c = t.baseCoin;
    if (transactions[i].baseCoin != NULL && transactions[i].baseCoin->abbreviation != NULL) {
      logger->println("--------");
      symbols[i] = transactions[i].baseCoin->abbreviation;
    }
  }
  
  //coinService->getMultipleSpotValues(symbols);

  delay(LOOP_DELAY);
  logger->println("Loop end");
}
