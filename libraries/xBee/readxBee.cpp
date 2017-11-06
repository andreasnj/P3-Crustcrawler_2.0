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

void xBeeClass::printReturn(char *pk){
}

void xBeeClass::readPacket(char *pk){//Populates a char array with a packet from the serial buffer.
  int counter = 0;
  int stopper = 0;
  char temp;
    /*do{
      //if(Serial.available()){
        temp = Serial.read();        //Reads the first element in serial buffer
          if(temp == START){          //Looking for the start delimiter
            pk[counter] = temp;
            counter++;
            }
          else {stopper++;}
      //}
    }while(counter == 0 || stopper < 10);
    do{
      //if(Serial.available()){        //Reads the rest of the package
        temp = Serial.read();
        pk[counter] = temp;
        counter++;
      //}
      
    }while(counter < 24);*/
}


bool xBeeClass::checkPacket(char *pk){//Generates checksum and compares with the one in the package
  char sum;
  for(int i = 3; i < 23; i++){       //Generate sum from index 3-to-22 (until, not incl. the checksum itself)
    sum = sum + pk[i];
  }
<<<<<<< HEAD
  
=======
>>>>>>> 5eaa63b4a9bc72f2ab9d0980bcd44fc2f9f5b0f3
  if((0xff - sum) == pk[23]){        //Check with the checksum of the package

    return true;                        //ok, good package
  }
  else{
    return false;                       //error
  }
}


/*
char xBeeClass::genChecksum(char *pk, int length){//Generates checksum
  char s = 0;
  for (int i = 0; i < length; i++)
    s += *(pk + i);
  return s;
}
*/

xBeeClass xBee;
