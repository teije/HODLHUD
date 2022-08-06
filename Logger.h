class Logger {  
  private:
    String _sourceName; // Name of the class calling the logger (makes it easier to see where the log is comming from)

  public:
    Logger() 
    {
      
    }

    void setSourceName(String sourceName) { _sourceName = sourceName; }
  
    void print(String text) { Serial.println("["+ _sourceName +"] \t" + text); }

    void printFloat(float floatValue, int decimalsToShow = 5) 
    { 
      Serial.print("["+ _sourceName +"] \t");
      Serial.println(floatValue, decimalsToShow); 
    }

};
