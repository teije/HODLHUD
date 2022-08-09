class Logger {  
  private:
    const int LABEL_CHARACTER_COUNT = 20;
  
    String _sourceName; // Name of the class calling the logger (makes it easier to see where the log is comming from)
    String _labelWhitespace = generateLabelWhitespace(_sourceName);

  public:
    Logger(String sourceName) 
    {
      _sourceName = sourceName;
      _labelWhitespace = generateLabelWhitespace(sourceName);
    }

    void setSourceName(String sourceName) { _sourceName = sourceName; }
  
    void println(String text) { Serial.println(_sourceName + _labelWhitespace + " > " + text); }
    void print(String text) { Serial.print(text); }

    void printFloat(float floatValue, int decimalsToShow = 5) 
    { 
      Serial.print(_sourceName + _labelWhitespace + " > ");
      Serial.println(floatValue, decimalsToShow); 
    }

    String generateLabelWhitespace(String sourceName) {
      int labelCharacterCount = LABEL_CHARACTER_COUNT;
      int sourceNameCharacterCount = sourceName.length();

      int differenceInCharacterCount = labelCharacterCount - sourceNameCharacterCount;

      if (differenceInCharacterCount < 0) {
        Serial.println("Source name too long! Shorten the name or increase the label character count!"); 
      }

      String whitespace = "";

      for (int i=0; i<differenceInCharacterCount; i++) {
        whitespace += " ";
      }

      return whitespace;
    }

};
