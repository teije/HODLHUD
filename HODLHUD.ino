/* TODO 
[ ] Add logger that can be disabled (0/1 or true/false) and won't be compiled when the debug bit is 0
[ ] Move transaction logic in main class to the transaction service
[ ] Clean up the API caller - can it be made more generic?
[ ] Add the ability to attempt to connect to multiple networks
    [ ] Add the ability to save wifi networks to EEPROM
    [ ] Add the ability to read the wifi credentials from a file (that won't be pushed to GIT)
        [ ] File does not exist yet? Create it with hints on the expected input
[ ] 
*/

// External libraries
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Project classes
#include "WiFiConnector.h"
#include "ApiCaller.h"
#include "TransactionService.h"

// Constants
const int LOOP_DELAY = 1000;

// Testing WiFi hotspot config
char ssid[]     = "Deepthought";
char password[] = "dont-forget-your-towel";

ApiCaller *apiCaller                   = new ApiCaller();
TransactionService *transactionService = new TransactionService(apiCaller);

void setup() {
  Serial.begin(9600);
  Serial.println("Setup start");

  // Test Hotspot WiFi configuration
  WiFiConnector* WiFiHotspot = new WiFiConnector(ssid, password);
  WiFiHotspot->connect();
  
  Serial.println("Setup end\n\n");
}

void loop() {  
  Serial.println("Loop start");

  JsonArray transactionsJsonArray = transactionService->getTransactions();
  
  Serial.println("||| Loop end");
  delay(LOOP_DELAY);
}
