#ifndef ESP32CLOCK
#define ESP32CLOCK

#include <NTPClient.h>

class ESP32Clock : public Base {
  public:
    bool clockHasBeenConfigured = false;
    
    ESP32Clock(WifiManager wifiManager) : timeClient(ntpUDP), wifiManager(wifiManager) { }

    /*
     * Configure the internal clock
     */
    void configureClock() {
      wifiManager.ensureConnection();

      println("Configuring clock... ");
      timeClient.begin();
      timeClient.setPoolServerName("pool.ntp.org");
      timeClient.setTimeOffset(3600);
      timeClient.update();
      clockHasBeenConfigured = true;
      print("done!");
    }

    /*
     * Check if the internal clock has already been configured
     */
    bool isConfigured() {
      if (!clockHasBeenConfigured) {
        println("The internal clock has not yet been configured", "warning");
        clockHasBeenConfigured = false;
        return false;
      }

      clockHasBeenConfigured = true;
      return true;
    }

    /*
     * Get the unix timestamp using the internal clock
     * A Unix timestamp is a number representation of milliseconds since January 1st, 1970
     * Mostly used for API calls
     * 
     * Why? More info & a unix-timestamp to readable-timestamp converter can be found here: 
     * https://www.unixtimestamp.com/
     */
    uint32_t getUnixTimestamp() {
      if (!isConfigured()) {
        configureClock();
      }

      uint32_t timestamp = timeClient.getEpochTime();
      
      println("Unix timestamp: ");
      Serial.printf("%u", timestamp);
      return timestamp;
    }

    /*
     * Get a human readable timestamp using the internal clock
     * Mostly used for the UI
     * 
     * Format:  yyyy-mm-dd hh:mm:ss
     * Example: 2023-03-03 09:06:36
     */
    String getHumanReadableTime() {
      if (!isConfigured()) {
        configureClock();
      }
      time_t now = timeClient.getEpochTime();
      struct tm timeinfo;
      gmtime_r(&now, &timeinfo);
      char buf[20];

      strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
      String humanReadableTime(buf);
      println("Human-readable time: ");
      print(humanReadableTime);
      return humanReadableTime;
    }

    /*
     * Parse a human readable timestamp to a unix timestamp
     * Format:  yyyy-mm-dd hh:mm:ss
     * To:      1234567890 (10 digit, milliseconds since January 1st, 1970)
     */
    uint32_t parseHumanReadableTimeToUnix(String timestamp) {
      if (!isConfigured()) {
        configureClock();
      }
      println("Parsing Human Readable time to Unix:" + String(timestamp));
      struct tm timeinfo = {};
      timeinfo.tm_year = atoi(timestamp.substring(0,4).c_str()) - 1900;
      timeinfo.tm_mon = atoi(timestamp.substring(5,7).c_str()) - 1;
      timeinfo.tm_mday = atoi(timestamp.substring(8,10).c_str());
      timeinfo.tm_hour = atoi(timestamp.substring(11,13).c_str());
      timeinfo.tm_min = atoi(timestamp.substring(14,16).c_str());
      timeinfo.tm_sec = atoi(timestamp.substring(17,19).c_str());
      time_t epoch_time = mktime(&timeinfo);
      uint32_t unix_time = epoch_time;
      println("Parsed Unix Timestamp: "+ String(unix_time));
      return unix_time;
    }
    
  private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    WifiManager wifiManager; // Manager to establish a wifi connection

    
    String Type() {
      return "ESP32Clock";
    }
};

#endif
