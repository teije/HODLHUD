#ifndef BASE
#define BASE

#include <typeinfo>
#pragma GCC diagnostic ignored "-fno-rtti"

/*
 * Base class provides shared functionality to derived classes, reducing code repetition and improving maintenance.
 */
class Base {
  public:  
    virtual String Type() {
      return "Base";
    }

    void println(String message) {
      String prefix = "\n[" + Type() + "] ";
      int prefixLength = prefix.length();
    
      // Determine the number of spaces to add based on the length of the prefix
      int spacesToAdd = 30 - prefixLength;
    
      // Add the required number of spaces to the end of the prefix
      for (int i = 0; i < spacesToAdd; i++) {
        prefix += " ";
      }
    
      Serial.print(prefix + message);
    }

    // A passthrough of the regular print method (to allow for easier to read code)
    void print(String message) {
      Serial.print(message);
    }
};
#endif // BASE
