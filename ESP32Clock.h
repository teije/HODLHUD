#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class ESP32Clock : public Base {
  public:
    bool clockHasBeenConfigured = false;
    
    ESP32Clock() : timeClient(ntpUDP) 
    { 
      
    }

    void configureClock() {
      println("Configuring clock... ");
      timeClient.begin();
      timeClient.setPoolServerName("pool.ntp.org");
      timeClient.setTimeOffset(3600);
      timeClient.update();
      clockHasBeenConfigured = true;
      print("done!");
    }

    bool isClockConfigured() {
      if (!clockHasBeenConfigured) {
        println("The internal clock has not yet been configured");
        return false;
      }
      
      return true;
    }

    uint32_t getUnixTimestamp() {
      if (!isClockConfigured()) {
        configureClock();
      }

      uint32_t timestamp = timeClient.getEpochTime();
      
      println("Unix timestamp: ");
      Serial.printf("%u", timestamp);
      return timestamp;
    }

    String getHumanReadableTime() {
      if (!isClockConfigured()) {
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

    uint32_t parseHumanReadableTime(String timestamp) {
      if (!isClockConfigured()) {
        configureClock();
      }
      struct tm timeinfo = {};
      timeinfo.tm_year = atoi(timestamp.substring(0,4).c_str()) - 1900;
      timeinfo.tm_mon = atoi(timestamp.substring(5,7).c_str()) - 1;
      timeinfo.tm_mday = atoi(timestamp.substring(8,10).c_str());
      timeinfo.tm_hour = atoi(timestamp.substring(11,13).c_str());
      timeinfo.tm_min = atoi(timestamp.substring(14,16).c_str());
      timeinfo.tm_sec = atoi(timestamp.substring(17,19).c_str());
      time_t epoch_time = mktime(&timeinfo);
      uint32_t unix_time = epoch_time;
      println("Parsed Unix to Human-Readable Timestamp: ");
      Serial.printf("%u", unix_time);
      return unix_time;
    }
    
  private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    
    String Type() {
      return "ESP32Clock";
    }
};
