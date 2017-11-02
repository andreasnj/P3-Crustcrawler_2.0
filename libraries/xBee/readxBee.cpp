#include "readxBee.h"

void xBeeClass::begin(long baud){

#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__) || defined(__AVR_ATmega2560__)
    Serial1.begin(baud);  // Set up Serial for Leonardo and Mega
    _serial = &Serial1;
#else
    Serial.begin(baud);   // Set up Serial for all others (Uno, etc)
    _serial = &Serial;
#endif

}

//##############################################################################
//############################ Public Methods ##################################
//##############################################################################


void xBeeClass::begin(HardwareSerial &HWserial, long baud){

    HWserial.begin(baud); // Set up Serial for a specified Serial object
    _serial = &HWserial;

}

void xBeeClass::begin(Stream &serial){

    _serial = &serial;  // Set a reference to a specified Stream object (Hard or Soft Serial)
}


//##############################################################################
//########################## Private Methods ###################################
//##############################################################################

void xBeeClass::printReturn(){

}

void readPacket(char *package){
  int counter = 0;
  char temp;
    do{
      if(Serial.available()){
        temp = Serial.read(); // reads the first element in serial buffer
          if(temp == 0x7e){
            package[counter] = temp;
            counter++;
            }
      }
    }while(counter == 0);
    do{
      if(Serial.available()){
        temp = Serial.read();
        package[counter] = temp;
        counter++;
      }
      
    }while(counter < 24);
  
  }


int checkPacket(char *package){
  char sum;
  for(int i = 3; i < 24; i++){
    sum = sum + package[i];
  }
  if(sum == 0x47){ //Check with the checksum of the package
    return 0; // ok, good package
  }
  else{
    return -1; // error
  }
}

xBeeClass xBee;
