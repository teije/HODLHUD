// External libraries
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "mbedtls/md.h"

class ApiCaller
{
  private:
    // Properties
    HTTPClient http;

    // Constants
    const String BINANCE_BASE_URL = "https://api.binance.com";
    char *BINANCE_API_KEY         = "y7ZTPqACsHNxFR5m2JDQ7SdgJ1mOaInXWJT74QWVo3jgTdgAWUVbjMBFZolcTopb";
    char *BINANCE_API_SECRET      = "TGdqRdsKQ3YtEBaOW9uOgBQbWXrD8QubAXUUfaGocZraOVRG3Hs5tjNQeWt8Tyxo";

    //https://sheets.googleapis.com/v4/spreadsheets/{sheet_id}/values/Sheet1!A1:D5?key={YOUR_API_KEY}
    //https://sheets.googleapis.com/v4/spreadsheets/spreadsheetId/values/Sheet1!A1:D5
    const String GOOGLE_BASE_URL            = "https://sheets.googleapis.com/v4/spreadsheets";
    const String GOOGLE_BASE_URL_MIDDLE     = "values";
    const String GOOGLE_BASE_URL_SUFFIX     = "?key=";
    const String GOOGLE_SHEET_ID            = "1geu-fnt5D6whhLoX8m_mC-AKpi6enbpTGn6bZ2PFQik";
    const String GOOGLE_API_KEY             = "AIzaSyCRrO7YUxzgkhW8kDI8j9I257QnuykSxH0";

  public:
    ApiCaller() { }

    //////////////////////////////////
    //////////// GOOGLE //////////////
    //////////////////////////////////

    /* Execute a call on the Google Sheet Api - with the supplied cell range */
    String executeGoogle(String pageTitle, String topLeftCell, String bottomRightCell) {
        String targetUrl = "";
        // Construct the full request url
        targetUrl = GOOGLE_BASE_URL         + "/" + 
                    GOOGLE_SHEET_ID         + "/" + 
                    GOOGLE_BASE_URL_MIDDLE  + "/" + 
                    pageTitle               + "!" + 
                    topLeftCell             + ":" + 
                    bottomRightCell         + 
                    GOOGLE_BASE_URL_SUFFIX  + 
                    GOOGLE_API_KEY;

        return get(targetUrl);
    }

    /* Get the number of transactions defined in the Google Sheet 'trades' page - this allows us to know which cell is the bottom one that contains a transaction  */
    int getTransactionCount() {
      String targetUrl        = "";
      String pageTitle        = "trades";
      String topLeftCell      = "A2";
      String bottomRightCell  = "A2";
      
      // Construct the full request url
      targetUrl = GOOGLE_BASE_URL         + "/" + 
                  GOOGLE_SHEET_ID         + "/" + 
                  GOOGLE_BASE_URL_MIDDLE  + "/" + 
                  pageTitle               + "!" + 
                  topLeftCell             + ":" + 
                  bottomRightCell         + 
                  GOOGLE_BASE_URL_SUFFIX  + 
                  GOOGLE_API_KEY;

      String response = get(targetUrl);

      DynamicJsonDocument jsonObject = responseToJsonDocument(response, 256);
      
      String transactionCount = jsonObject["values"][0][0];

      //Serial.println("Extracted transaction count from json response: " + transactionCount);
      
      return transactionCount.toInt();
    }

    /* Get all gransactions defined in the Google Sheets 'trades' page */
    String getTransactions() {
      String targetUrl              = "";
      String pageTitle              = "trades";
      int headerRowCount            = 3;
      int transactionCount          = getTransactionCount();
      String topLeftCell            = "A4";
      String bottomRightCell_Letter = "J";
      String bottomRightCell_Number = String(headerRowCount + transactionCount);
      String bottomRightCell        = bottomRightCell_Letter + bottomRightCell_Number;
      
      // Construct the full request url
      targetUrl = GOOGLE_BASE_URL         + "/" + 
                  GOOGLE_SHEET_ID         + "/" + 
                  GOOGLE_BASE_URL_MIDDLE  + "/" + 
                  pageTitle               + "!" + 
                  topLeftCell             + ":" + 
                  bottomRightCell         + 
                  GOOGLE_BASE_URL_SUFFIX  + 
                  GOOGLE_API_KEY;

      return get(targetUrl);
    }

    /* Get the value of a single cell in the provided Google Sheet page */
    String getCellValue(String pageName, String cell) {
      String response = executeGoogle(pageName, cell, cell);
      
      DynamicJsonDocument jsonObject = responseToJsonDocument(response, 64);
      const char* value = jsonObject["values"][0][0];
      
      return value;
    }

    /* Get all values within a grid marked by the top left- and bottom right cell */
    String getCellRangeValues(String pageName, String topLeftCell, String bottomRightCell) {
      return executeGoogle(pageName, topLeftCell, bottomRightCell);
    }



    //////////////////////////////////
    //////////// BINANCE /////////////
    //////////////////////////////////

    /* Execute an API call on the supplied Binance endpoint (along with the required parameters) */
    String executeBinance(String endpoint, String queryParameterString, bool requiresAuth) {
      String timestamp      = getTimestamp();
        const char *payload = ("timestamp=" + timestamp + queryParameterString).c_str();
        String signature    = parseSignature(payload);

        String targetUrl = "";

        // Construct the full request url
        if (requiresAuth) {
          targetUrl          = 
            BINANCE_BASE_URL + 
            endpoint         +
            "?timestamp="    + 
            timestamp        + 
            "&signature="    + 
            signature        +
            queryParameterString;  
        } else {
          targetUrl          = 
            BINANCE_BASE_URL + 
            endpoint         +
            queryParameterString;
        }
        
        return get(targetUrl);
    }

    /* Check if a connection can be established to binance */
    bool hasBinanceApiConnection() {
      String timestamp    = getTimestamp();
      
      const char *payload = ("timestamp=" + timestamp).c_str();
      String signature = parseSignature(payload);
      bool isConnected = false;
      
      String targetUrl = 
        BINANCE_BASE_URL + 
        "/api/v3/ping";
      
      http.begin(targetUrl.c_str()); // Start API request with the constructed url

      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-MBX-APIKEY", BINANCE_API_KEY);

      int responseCode = http.GET(); // Send HTTP GET request to the server. The response data is stored in the jsonResponse variable
      
      String response = "";
      
      if (responseCode > 0) {
        return true;
      }
      
      return false;
    }

    /* Get the value of 1 USD to EUR */
    float getUSDtoEURrate() {
      String response = executeBinance("/api/v3/ticker/price", "?symbol=EURUSDT", false);

      DynamicJsonDocument jsonObject = responseToJsonDocument(response, 300);
      jsonObject.shrinkToFit();
      
      const char* valueString = jsonObject["price"];
      float rate = strtof(valueString, NULL);
      
      //Serial.print("Fetched EUR to USDT Rate: ");
      //Serial.println(rate);

      return rate;
    }

    /* Get the value of 1 EUR to USD (by inverting the USD to EUR value) */
    float getEURtoUSDrate() {
      float rate = getUSDtoEURrate();
      float inverseRate = 1 / rate;
      
      //Serial.print("Fetched USDT to EUR Rate: ");
      //Serial.println(inverseRate, 5);
      
      return inverseRate;
    }
    
    /////////////////////////////////
    /////////// GENERIC /////////////
    /////////////////////////////////

    /* Perform a GET request on the provided targetUrl */
    String get(String targetUrl) {
      http.begin(targetUrl.c_str()); // Start API request with the constructed url

      Serial.println("Executing GET request on: " + targetUrl);

      int responseCode = http.GET(); // Send HTTP GET request to the server. The response data is stored in the jsonResponse variable
      
      String response = "";
      
      if (responseCode > 0) {        //Check for the returning code
        response = http.getString();
        
        if (response == "") {
          // The response was empty
        }
      } else if (responseCode < 0) {
        // Response received, but API call was not executed succesfully
      } else {
        // API call was not executed succesfully");
      }
     
      http.end();

        return response;
    }

    /* Parse an API response (in String format) to a JsonDocument (from the ArduinoJson.h library) */
    DynamicJsonDocument responseToJsonDocument(String response, int reservedMemorySize = 1024) {
      DynamicJsonDocument jsonObject(reservedMemorySize); // Reserving memory space to hold the json object
      deserializeJson(jsonObject, response);              // Converting from a string to a json object
      jsonObject.shrinkToFit();                           // Shrink memory size to fit the content

      return jsonObject;
    }
    
    /* This method grabs the current time (as a timestamp), which is required for other API calls */
    String getTimestamp() {
      String targetUrl = "https://worldtimeapi.org/api/timezone/Etc/UTC";   // Set target URL to the time API
        
      String response = get(targetUrl);                                     // Get the response as a String

      DynamicJsonDocument jsonObject = responseToJsonDocument(response, 256);
      
      String timestamp_seconds       = jsonObject["unixtime"];              // Grabbing the unix timestamp from the jsonObject
      String timestamp_milliseconds  = timestamp_seconds + "000";           // 'Convert' to miliseconds
      
      http.end();                                                           // End API request to free up resources

      return timestamp_milliseconds;
    }

    /* Parse a payload into a signature that can be used for Binance API calls */
    String parseSignature(const char *payload) {
        /* HMAC Shizzle */
        String signature = "";                                                                // Signature variable to store the entire value
        
        byte hmacResult[32];                                                                  // Stores the authentication message
        mbedtls_md_context_t ctx;                                                             // Variable to keep context across calls
        mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;                                        // Define the hashing algorithm (SHA-256 in this case)
        const size_t payloadLength = strlen(payload);                                         // Define the length of the payload
        const size_t keyLength = strlen(BINANCE_API_SECRET);                                  // Define the length of the secret key
        mbedtls_md_init(&ctx);                                                                // Initialize the context
        mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);                        // Select hash function and allocate internal structures
        mbedtls_md_hmac_starts(&ctx, (const unsigned char *) BINANCE_API_SECRET, keyLength);  // Start hashing
        mbedtls_md_hmac_update(&ctx, (const unsigned char *) payload, payloadLength);
        mbedtls_md_hmac_finish(&ctx, hmacResult);                                             // Get the output authentication code
        mbedtls_md_free(&ctx);                                                                // Free and clear the internal structures of the context

        for(int i= 0; i< sizeof(hmacResult); i++){
            char str[3];
       
            sprintf(str, "%02x", (int)hmacResult[i]);
            signature += str;
        }

        return signature;
    }
};
