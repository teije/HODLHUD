class Logger {  
  private:
    String loggerSourceName; // Name of the class calling the logger (makes it easier to see where the log is comming from)

  public:
    Logger(String LoggerSourceName) {
      loggerSourceName = LoggerSourceName; 
    }
  
    void print(String text) { Serial.println("["+ loggerSourceName +"] \t" + text); }
};
