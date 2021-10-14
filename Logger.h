class Logger {  
  private:
    String LoggerSourceName; // Name of the class calling the logger (makes it easier to see where the log is comming from)

  public:
    Logger(String loggerSourceName) {
      LoggerSourceName = loggerSourceName;
    }
  
    void print(String text) { Serial.println("["+ LoggerSourceName +"] \t" + text); }
};
