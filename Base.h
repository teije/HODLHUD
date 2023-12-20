#ifndef BASE
#define BASE

#pragma GCC diagnostic ignored "-fno-rtti"

/*
 * Base class provides shared functionality to derived classes, reducing code repetition and improving maintenance.
 */
class Base {
  public:  
    virtual String Type() {
      return "Base";
    }

    void println(String message, String messageType = "") {
      String prefix = "\n[" + Type() + "] ";
      
      int prefixLength = prefix.length();
    
      // Determine the number of spaces to add based on the length of the prefix
      int spacesToAdd = 30 - prefixLength;
    
      // Add the required number of spaces to the end of the prefix
      for (int i = 0; i < spacesToAdd; i++) {
        prefix += " ";
      }

      // Add optional marker based on type
      if (messageType == "error") // Use for critically breaking things
      {
        message = "✖ " + message;
      }
      else if (messageType == "warning") // Use for non-critical breaking things, but should not be this way
      {
        message = "⚠ " + message;
      }
      else if(messageType == "todo") // Use to include to-do's in the logs
      {
        message = "⚑ " + message;
      }
      else if(messageType == "configure") // Use for code that configures things to make them easier to spot
      {
        message = "⚙ " + message;
      }
      else // add empty spaces so messages align
      {
        message = "  " + message;
      }
    
      Serial.print(prefix + message);
    }

    // A passthrough of the regular print method (to allow for easier to read code)
    void print(String message) {
      Serial.print(message);
    }
};
#endif // BASE
