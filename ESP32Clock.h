#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class ESP32Clock : public Base {
  private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;
    bool clockHasBeenConfigured = false;

  public:
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

    const String type() override {
      return "ESP32Clock.h";
    }
};
