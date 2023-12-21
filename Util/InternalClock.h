#ifndef INTERNAL_CLOCK
#define INTERNAL_CLOCK

#include <NTPClient.h>

class InternalClock {
  public:
    bool ClockIsConfigured = false;

    InternalClock(WiFiManager wifiManager) : TimeClient(NtpUDP), WifiManager(wifiManager) { }

    /*
       Configure the internal clock
    */
    void ConfigureClock() {
      WifiManager.EnsureConnection();

      TimeClient.begin();
      TimeClient.setPoolServerName("pool.ntp.org");
      TimeClient.setTimeOffset(3600);
      TimeClient.update();
      ClockIsConfigured = true;
      //println("Configured clock", "configure");
    }

    /*
       Check if the internal clock has already been configured
    */
    bool IsConfigured() {
      if (!ClockIsConfigured) {
        //println("The internal clock has not yet been configured", "warning");
        ClockIsConfigured = false;
        return false;
      }

      ClockIsConfigured = true;
      return true;
    }

    /*
       Get the unix timestamp using the internal clock
       A Unix timestamp is a number representation of milliseconds since January 1st, 1970
       Mostly used for API calls

       Why? More info & a unix-timestamp to readable-timestamp converter can be found here:
       https://www.unixtimestamp.com/
    */
    uint32_t GetUnixTimestamp() {
      if (!IsConfigured()) {
        ConfigureClock();
      }

      uint32_t timestamp = TimeClient.getEpochTime();
      return timestamp;
    }

    String GetCurrentTime() 
    {
      return GetHumanReadableDateTime().substring(11);
    }
    String GetCurrentDate()
    {
      String dateString = GetCurrentDay() + "-";
      dateString += GetCurrentMonth() + "-";
      dateString += GetCurrentYear();
      return dateString;
    }
    String GetCurrentYear() 
    {
      return GetHumanReadableDateTime().substring(0, 4);
    }
    String GetCurrentMonth() 
    {
      return GetHumanReadableDateTime().substring(5, 7);
    }
    String GetCurrentDay() 
    {
      return GetHumanReadableDateTime().substring(8, 10);
    }

    /*
       Get a human readable timestamp using the internal clock
       Mostly used for the UI

       Format:  yyyy-mm-dd hh:mm:ss
       Example: 2023-03-03 09:06:36
    */
    String GetHumanReadableDateTime() {
      // Ensure that the clock is configured
      if (!IsConfigured()) {
        ConfigureClock();
      }
      
      // Get the time as milliseconds (i.e.: 1234567890 - 10 digit, milliseconds since January 1st, 1970)
      time_t now = TimeClient.getEpochTime();
      struct tm timeinfo;
      gmtime_r(&now, &timeinfo);
      char buf[20];

      // Format and print so the time is actually readable
      strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
      String humanReadableTime(buf);
      return humanReadableTime;
    }

    /*
       Parse a human readable timestamp to a unix timestamp
       Format:  yyyy-mm-dd hh:mm:ss
       To:      1234567890 (10 digit, milliseconds since January 1st, 1970)
    */
    uint32_t ParseHumanReadableTimeToUnix(String timestamp) {
      if (!IsConfigured()) {
        ConfigureClock();
      }
      //println("Parsing Human Readable time to Unix:" + String(timestamp));
      struct tm timeinfo = {};
      timeinfo.tm_year = atoi(timestamp.substring(0, 4).c_str()) - 1900;
      timeinfo.tm_mon = atoi(timestamp.substring(5, 7).c_str()) - 1;
      timeinfo.tm_mday = atoi(timestamp.substring(8, 10).c_str());
      timeinfo.tm_hour = atoi(timestamp.substring(11, 13).c_str());
      timeinfo.tm_min = atoi(timestamp.substring(14, 16).c_str());
      timeinfo.tm_sec = atoi(timestamp.substring(17, 19).c_str());
      time_t epoch_time = mktime(&timeinfo);
      uint32_t unix_time = epoch_time;
      //println("Parsed Unix Timestamp: " + String(unix_time));
      return unix_time;
    }

  private:
    WiFiUDP NtpUDP;
    NTPClient TimeClient;
    WiFiManager WifiManager; // Manager to establish a wifi connection
};

#endif
