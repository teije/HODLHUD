#include <typeinfo>
#pragma GCC diagnostic ignored "-fno-rtti"

#ifndef BASE
#define BASE
class Base {
  public:
    virtual const String toString() {
      return "Base.h";
    }

    void print(String message) {
      Serial.print(message);
    }

    void println(String message) {
      Serial.print("\n[" + toString() + "] " + message);
    }
};
#endif // BASE
