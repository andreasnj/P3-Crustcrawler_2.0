#include <readxBee.h>

#define xBee_Baudrate 115200

void setup(){
  Serial1.begin(xBee_Baudrate);
  Serial.begin(xBee_Baudrate);
  xBee.begin(Serial1);
  Serial.println("reset");
  delay(500);
  Serial1.flush(); 
}

int tempPk[24] = {};
int x=0, y=0, z=0, emg1=0, emg2=0;
int pass = 0;
int fail = 0;
float rate;

void loop() {
  for(int i = 0; i < 100; i++){
    xBee.readPacket(tempPk);
    //xBee.decodePacket(tempPk); //This compiles, but doesn't seem to work
    x = tempPk[14] + (tempPk[13] << 8);
    y = tempPk[16] + (tempPk[15] << 8);
    z = tempPk[18] + (tempPk[17] << 8);
    emg1 = tempPk[20] + (tempPk[19] << 8);
    emg2 = tempPk[22] + (tempPk[21] << 8);
    Serial.print("x = "); Serial.print(x); //Printing the received data
    Serial.print(" y = "); Serial.print(y);
    Serial.print(" z = "); Serial.print(z);
    Serial.print(" emg1 = "); Serial.print(emg1);
    Serial.print(" emg2 = "); Serial.print(emg2);

      if(xBee.checkPacket(tempPk)){ //Check and print if the package passed
        Serial.println("| INT -- PASS |"); pass++;
        }
        else{Serial.println("| INT -- FAIL |"); fail++;
        }
  }
  Serial.println(pass); //Print the pass and fail counts and rate
  Serial.println(fail);
  rate = (float)pass/(pass+fail);
  Serial.println(rate*100);
}
