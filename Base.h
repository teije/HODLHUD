#ifndef BASE
#define BASE

#include <typeinfo>
#pragma GCC diagnostic ignored "-fno-rtti"

class Base {
  public:  
    virtual const String type() {
      return "Base.h";
    }

    virtual const String ToString() {
      return "Base class - not intended to be initialized";
    }

    void print(String message) {
      Serial.print(message);
    }

    void println(String message) {
      Serial.print("\n[" + type() + "] " + message);
    }

    void printCreateMessage() {
      Serial.print("\n[" + type() + "] created!");
    }
};
#endif // BASE
