#include "readingxBee.h"

void xBeeClass::begin(long baud){

#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__) || defined(__AVR_ATmega2560__)
    Serial1.begin(baud);  // Set up Serial for Leonardo and Mega
    _serial = &Serial1;
#else
    Serial.begin(baud);   // Set up Serial for all others (Uno, etc)
    _serial = &Serial;
#endif

}

void xBeeClass::begin(HardwareSerial &HWserial, long baud){

    HWserial.begin(baud); // Set up Serial for a specified Serial object
    _serial = &HWserial;

}

void xBeeClass::begin(Stream &serial){

    _serial = &serial;  // Set a reference to a specified Stream object (Hard or Soft Serial)

}

xBeeClass xBee;
