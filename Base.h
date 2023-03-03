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

    // A more verbose method to print to the serial monitor
    void println(String message) {
      Serial.print("\n[" + Type() + "] " + message);
    }
    // A passthrough of the regular print method (to allow for easier to read code)
    void print(String message) {
      Serial.print(message);
    }
};
#endif // BASE
