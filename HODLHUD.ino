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
const int TRANSACTION_FIELD_COUNT    = 10;
const char* variable_labels[10] = {
  "Show on HUD",
  "Base title",
  "Base symbol",
  "Base amount",
  "Counter title",
  "Counter symbol",
  "Counter amount",
  "Date",
  "Remarks",
  "Value in EUR",
};

const int TRANSACTION_SHOW_ON_HUD    = 0;
const int TRANSACTION_BASE_TITLE     = 1;
const int TRANSACTION_BASE_SYMBOL    = 2;
const int TRANSACTION_BASE_AMOUNT    = 3;
const int TRANSACTION_COUNTER_TITLE  = 4;
const int TRANSACTION_COUNTER_SYMBOL = 5;
const int TRANSACTION_COUNTER_AMOUNT = 6;
const int TRANSACTION_DATE           = 7;
const int TRANSACTION_REMARKS        = 8;
const int TRANSACTION_VALUE_IN_EUR   = 9;


// Testing WiFi hotspot config
const char ssid[]     = "Deepthought";
const char password[] = "dont-forget-your-towel";

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
  
  int transactionCount  = transactionService->getTransactionCount();            // Fetch number of transactions in the google sheet
  int transactionObjectSize = 300;                                              // In JSON a transaction costs about 300 memory units
  int jsonDocumentSize  = transactionCount * transactionObjectSize;             // Calculate the size by multiplying the units per transaction * amount of transactions
  String responseString = transactionService->getTransactions();                // Grabbing transactions from the Google Sheet

  DynamicJsonDocument jsonDocument(jsonDocumentSize);                           // Reserving memory space to hold the json object
  DeserializationError error = deserializeJson(jsonDocument, responseString);   // Converting from the api response string to a json object we can work with

  if (error) {                                                                  // Throw error if serialization fails (happens usually when loading too many transactions - so far >~200)
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  jsonDocument.shrinkToFit();                                                    // Shrink memory size to fit the content & to not waste any memory

  JsonArray jsonValuesArray = jsonDocument["values"];

  for (int i=0; i<jsonValuesArray.size(); i++) {                                 // Print all values for each transaction
    for(int j=0; j<TRANSACTION_FIELD_COUNT; j++) {
      Serial.print(variable_labels[j]);
      Serial.print(':');
      Serial.println(jsonValuesArray[i][j].as<const char*>());
    }
    
    Serial.println('\n');
  }
  
  Serial.println("||| Loop end");
  delay(LOOP_DELAY);
}
