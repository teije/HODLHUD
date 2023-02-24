#ifndef INTERNALCLOCK
#define INTERNALCLOCK

#include "Base.h"
#include "WifiManager.h"
#include <time.h>

class InternalClock : public Base {
  public:
     InternalClock(WifiManager wifiManager){}
  
    void setClock() {
      // Set timezone
      setenv("TZ", timezone, 1);
      tzset();
      
      // Set time using NTP
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      
      // Wait for time to be set
      time_t now = time(nullptr);
      while (now < epochTime) {
        delay(1000);
        now = time(nullptr);
      }
    }

  private:
    const char* timezone = "CET-1CEST,M3.5.0/2,M10.5.0/3";  // POSIX-style time zone string for Amsterdam, Netherlands
    const char* ntpServer = "pool.ntp.org";                 // Address of the server to synchronize the clock with
    const long gmtOffset_sec = 3600;                        // GMT offset of Central European Time (CET), which is UTC+1
    const int daylightOffset_sec = 3600;                    // Daylight saving time offset is also 1 hour
    const time_t epochTime = 1514764800;                    // January 1, 2022, 00:00:00 in CET (UTC+1)
};

#endif
