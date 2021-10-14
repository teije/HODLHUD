class Logger {  
  private:

  public:
    String LoggerSourceName; 
  
    Logger(String loggerSourceName) {
      LoggerSourceName = loggerSourceName;
    }
  
    void print(String text) { Serial.println("["+ LoggerSourceName +"] \t" + text); }
};
