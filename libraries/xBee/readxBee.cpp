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



void xBeeClass::printReturn(char *pk){
}

void xBeeClass::readPacket(char *pk){//Populates a char array with a packet from the serial buffer.
  int counter = 0;
  char temp;
    do{
      if(Serial.available() > 0){
        temp = Serial.read();        //Reads the first element in serial buffer
          if(temp == 0x7e){          //Looking for the start delimiter
            pk[counter] = temp;
            counter++;
            }
      }
      else {break;};
    }while(counter == 0);
    do{
      if(Serial.available() > 0){        //Reads the rest of the package
        temp = Serial.read();
        pk[counter] = temp;
        counter++;
      }
      else {break;};
    }while(counter < 24);
}

bool xBeeClass::checkPacket(char *pk){//Generates checksum and compares with the one in the package
  char sum;
  for(int i = 3; i < 23; i++){       //Generate sum from index 3-to-22 (until, not incl. the checksum itself)
    sum = sum + pk[i];
  }
  if((0xff - sum) == pk[23]){        //Check with the checksum of the package
    return true;                     //ok, good package
  }
  else{
    return false;                    //error
  }
}

void xBeeClass::decodePacket(char *pk, int i){//Convert chars from packet into int, store in arrays, average
  emg1arr[i] = (int)((pk[19] << 8) | pk[20]);
  emg2arr[i] = (int)((pk[21] << 8) | pk[22]);
  accZarr[i] = (int)((pk[13] << 8) | pk[14]);
  accYarr[i] = (int)((pk[15] << 8) | pk[16]);
  accXarr[i] = (int)((pk[17] << 8) | pk[18]);

  emg1 = xBee.averageArr(emg1arr);
  emg2 = xBee.averageArr(emg2arr);

  emg1arr[i] = emg1 = (int)((pk[19] << 8) | pk[20]);
  emg2arr[i] = emg2 = (int)((pk[21] << 8) | pk[22]);
  accZarr[i] = accZ = (int)((pk[13] << 8) | pk[14]);
  accYarr[i] = accY = (int)((pk[15] << 8) | pk[16]);
  accXarr[i] = accX = (int)((pk[17] << 8) | pk[18]);

  emg1 =
}

float xBeeClass::averageArr(int *arr, int length){
  int s = 0;
  for(i = 0; i < length; i++){
    s += arr[i];
  }
  float avg = s/length;
  return(avg);
}

//##############################################################################
//########################## Private Methods ###################################
//##############################################################################

xBeeClass xBee;
