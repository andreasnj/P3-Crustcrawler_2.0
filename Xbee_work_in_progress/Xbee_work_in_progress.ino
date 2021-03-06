#include <readxBee.h>
#include <SoftwareSerial.h>

#define xBee_Baudrate 115200

SoftwareSerial mySerial(10,11);

/*
   Format for XBEE packets
    0 0x7e  - start ch
    1 0x00  - length msb
    2 0x14  - length lsb
    3 0x83  - API frame identifier
    4 0x56  - senders address
    5 0x78  - senders address
    6 0x43  - received signal strength - RSI
    7 0x00  - option byte
    8 0x01  - nu,mber of samples
    9 0x3e  - channel indicator mask n/a A5 A4 A3 A2 A1 A0 D8
   10 0xe0  - channel indicatot mask  D7 D6 D5 D4 D3 D2 D1 D0
   11 0x00  - digital sample (msb)
   12 0x40  - digital sample (lsb)

   13 0x??  - Acc Z (msb)
   14 0x??  - Acc Z (lsb)

   15 0x??  - Acc Y (msb)
   16 0x??  - Acc Y (lsb)

   17 0x??  - Acc X (msb)
   18 0x??  - Acc X (lsb)

   19 0x??  - EMG ch1 (msb)
   20 0x??  - EMG ch1 (lsb)

   21 0x??  - EMG ch2 (msb)
   22 0x??  - EMG ch2 (lsb)

   23 0x??  - checksum

   The checksum is all bytes added together excl the first three. The sum including(!) the checksum shall give 0xff
   Strategy sum all bytes excluding first three. The checksum will be 0xff - sum
*/

int testPk[24] = {0x7e, 0x00, 0x14, 0x83, 0x56, 0x78, 0x43, 0x00, 0x01, 0x3e,
                    0xe0, 0x00, 0x40, 0x02, 0x9b, 0x02, 0x1a, 0x02, 0x05, 0x00,
                    0x00, 0x00, 0x05, 0x47};  // from datasheet

int tempPk[24] = {}; //Initializes array (See if it works only doing it in setup???)

byte temp;

void setup() {
  Serial.begin(xBee_Baudrate);
  Serial1.begin(115200);
  Serial.flush();
  mySerial.begin(xBee_Baudrate);
  xBee.begin(mySerial);
  while (! Serial){                 // wait until serial port is up and running
  }
  Serial.println("Reset");
  delay(500); // just to be sure
}

void loop() {
  /*if(Serial1.available()){
    temp = Serial1.read();    
    if (temp == 0x7E){
          tempPk[0] = temp;
          for (int i = 1; i < 24 ; i++){
            temp = Serial1.read();
            tempPk[i] = temp;
          }
          }
  }*/
  //Ready for new package
  xBee.readPacket(tempPk);
  if(xBee.checkPacket(tempPk)){
    Serial.println("Received and passsed");
    Serial.println(tempPk[23]);
    }
    else{Serial.println("-");
        Serial.println(tempPk[0]);
        Serial.println(tempPk[1]);
        Serial.println(tempPk[2]);
        
        Serial.println(tempPk[23]);};
    
/*
  if(xBee.checkPacket(testPk)){
  //Do stuff
    Serial.println("The test package passed checksum"); //Needs testing
    }
    else{Serial.println("Does not work");};*/
}
