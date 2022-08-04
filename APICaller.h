#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "mbedtls/md.h"

class APICaller
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

    // Services
    Logger* logger = new Logger("APICaller");

    String resolveBaseUrl(String ApiName) {
      if (ApiName == "Binance") {
       return BINANCE_BASE_URL;
      } else {
        return "null";
      }
    }
     
  public:
    APICaller(String ApiName) {
      apiName     = ApiName;
      apiBaseUrl  = resolveBaseUrl(ApiName);
      
      logger->print("New APICaller created for: " + apiName + " with base url: " + apiBaseUrl);
    }
    
    String execute(String endpoint, String queryParameterString = "", bool requiresAuth = false) {
        String timestamp    = getTimestamp();
        const char *payload = ("timestamp=" + timestamp + queryParameterString).c_str();
        String signature    = parseSignature(payload);

        String targetUrl = "";

        // Construct the full request url
        if (requiresAuth) {
          targetUrl = 
            apiBaseUrl + 
            endpoint +
            "?timestamp=" + timestamp + "&signature=" + signature +
            queryParameterString;  
        } else {
          targetUrl = 
            apiBaseUrl + 
            endpoint +
            queryParameterString;
        }
        
        logger->print("Executing GET request on: " + targetUrl);
        
        http.begin(targetUrl.c_str()); // Start API request with the constructed url

        http.addHeader("Content-Type", "application/json");
        http.addHeader("X-MBX-APIKEY", BINANCE_API_KEY);

        int responseCode = http.GET(); // Send HTTP GET request to the server. The response data is stored in the jsonResponse variable
        
        String response = "";
        
        if (responseCode > 0) { //Check for the returning code
          response = http.getString();
          logger->print("Response Code (" + String(responseCode) + ") " + response);
          if (response == "") {
            logger->print("The response was empty");
          }
        } else if (responseCode < 0) {
          logger->print("Response Code (" + String(responseCode) + ") Response received, but API call was not executed succesfully");
        } else {
          logger->print("Response Code (" + String(responseCode) + ") API call was not executed succesfully");
        }
       
        http.end();
        
        return response;
    }

    /* This method grabs the current time (as a timestamp), which is required for other API calls */
    String getTimestamp() {
      String targetUrl = "https://worldtimeapi.org/api/timezone/Etc/UTC"; // Set target URL to the time API
        
      logger->print("Fetching timestamp from: " + targetUrl);                    
      http.begin(targetUrl.c_str());          // Start API request with the constructed url
      
      int responseCode = http.GET();          // Send the request
      String response = http.getString();     // Get the response as a String
      
      DynamicJsonDocument jsonObject(1024);   // Reserving memory space to hold the json object
      deserializeJson(jsonObject, response);  // Converting from a string to a json object

      // The json object contains the following properties:
      /*{
          "abbreviation": "CEST",
          "client_ip": "94.168.86.251",
          "datetime": "2021-10-18T12:53:05.626733+02:00",
          "day_of_week": 1,
          "day_of_year": 291,
          "dst": true,
          "dst_from": "2021-03-28T01:00:00+00:00",
          "dst_offset": 3600,
          "dst_until": "2021-10-31T01:00:00+00:00",
          "raw_offset": 3600,
          "timezone": "Europe/Amsterdam",
          "unixtime": 1634554385,
          "utc_datetime": "2021-10-18T10:53:05.626733+00:00",
          "utc_offset": "+02:00",
          "week_number": 42
      }*/

      String timestamp_seconds = jsonObject["unixtime"]; // Grabbing the unix timestamp from the jsonObject
      logger->print("JSON Object timestamp seconds: " + timestamp_seconds);
      
      String timestamp_milliseconds  = timestamp_seconds + "000"; // 'Convert' to miliseconds
      logger->print("JSON Object timestamp milliseconds: " + timestamp_milliseconds);

      logger->print("Extracted timestamp (milliseconds/UNIX) from JSON object: " + timestamp_milliseconds);

      http.end(); // End API request to free up resources

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

        logger->print("Generated signature: " + signature);

        return signature;
    }

    bool hasBinanceApiConnection() {
      String timestamp    = getTimestamp();
        const char *payload = ("timestamp=" + timestamp).c_str();
        String signature = parseSignature(payload);
        bool isConnected = false;
        
        String targetUrl = 
          apiBaseUrl + 
          "/api/v3/ping";  
        
        logger->print("Executing GET request on: " + targetUrl);
        
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
};
