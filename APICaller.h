// External libraries
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "mbedtls/md.h"

class ApiCaller
{
  private:
    // Properties
    String apiName;
    String apiBaseUrl;
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

      DynamicJsonDocument jsonObject = responseToJsonObject(response, 256);
      
      String transactionCount = jsonObject["values"][0][0];

      //_logger->println("Extracted transaction count from json response: " + transactionCount);
      
      return transactionCount.toInt();
    }

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
    
    String getCellValue(String pageName, String cell) {
      String response = executeGoogle(pageName, cell, cell);

      //DynamicJsonDocument jsonObject(64);   // Reserving memory space to hold the json object
      //responseToJsonObject(jsonObject, response);  // Converting from a string to a json object

    DynamicJsonDocument jsonObject = responseToJsonObject(response, 64);
      
      const char* value = jsonObject["values"][0][0];
      
      return value;
    }

    String getCellRangeValues(String pageName, String topLeftCell, String bottomRightCell) {
      String response = executeGoogle(pageName, topLeftCell, bottomRightCell);

      //DynamicJsonDocument jsonObject(256);    // Reserving memory space to hold the json object
      //responseToJsonObject(jsonObject, response);  // Converting from a string to a json object
      //jsonObject.shrinkToFit();

      DynamicJsonDocument jsonObject = responseToJsonObject(response, 256);
      
      const char* value = jsonObject["values"];
      
      //_logger->println("Fetched cell range values: " + (String)value);
    }


    //////////////////////////////////
    //////////// BINANCE /////////////
    //////////////////////////////////

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

    float getUSDtoEURrate() {
      String response = executeBinance("/api/v3/ticker/price", "?symbol=EURUSDT", false);

      //DynamicJsonDocument jsonObject(256);   // Reserving memory space to hold the json object
      //responseToJsonObject(jsonObject, response);  // Converting from a string to a json object

      DynamicJsonDocument jsonObject = responseToJsonObject(response, 256);
      
      jsonObject.shrinkToFit();
      const char* valueString = jsonObject["price"];
      float rate = strtof(valueString, NULL);
      
      //_logger->println("Fetched EUR to USDT Rate: ");
      //_logger->printFloat(rate);

      return rate;
    }

    float getEURtoUSDrate() {
      float rate = getUSDtoEURrate();
      float inverseRate = 1 / rate;
      
      //_logger->println("Fetched USDT to EUR Rate: ");
      //_logger->printFloat(inverseRate);
      
      return inverseRate;
    }

    
    bool hasBinanceApiConnection() {
      String timestamp    = getTimestamp();
      
      const char *payload = ("timestamp=" + timestamp).c_str();
      String signature = parseSignature(payload);
      bool isConnected = false;
      
      String targetUrl = 
        apiBaseUrl + 
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

    /////////////////////////////////
    //////////// OTHER //////////////
    /////////////////////////////////

        
    String get(String targetUrl) {
      http.begin(targetUrl.c_str()); // Start API request with the constructed url

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

    JsonArray responseToJsonArray(String response, int reservedMemorySize = 1024) {
      DynamicJsonDocument jsonDoc(reservedMemorySize); // Reserving memory space to hold the json object
      deserializeJson(jsonDoc, response);              // Converting from a string to a json object
      jsonDoc.shrinkToFit();                        // Shrink memory size to fit the content
      JsonArray jsonArray = jsonDoc.as<JsonArray>();

      return jsonArray;
    }
    
    /* This method grabs the current time (as a timestamp), which is required for other API calls */
    String getTimestamp() {
      String targetUrl = "https://worldtimeapi.org/api/timezone/Etc/UTC";   // Set target URL to the time API
        
      String response = get(targetUrl);                                     // Get the response as a String

      DynamicJsonDocument jsonObject = responseToJsonObject(response, 256);
      
      String timestamp_seconds       = jsonObject["unixtime"];              // Grabbing the unix timestamp from the jsonObject
      String timestamp_milliseconds  = timestamp_seconds + "000";           // 'Convert' to miliseconds
      
      http.end();                                                           // End API request to free up resources

      return timestamp_milliseconds;
    }

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
