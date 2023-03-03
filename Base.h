#ifndef BASE
#define BASE

#include <typeinfo>
#pragma GCC diagnostic ignored "-fno-rtti"

class Base {
  public:  
    virtual String Type() {
      return "Base";
    }

    //virtual const String ToString() {
    //  return "Base class - not intended to be initialized";
    //}

    void print(String message) {
      Serial.print(message);
    }

    void println(String message) {
      Serial.print("\n[" + Type() + "] " + message);
    }
};
#endif // BASE
