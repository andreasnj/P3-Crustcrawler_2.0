#include "readxBee.h"
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

char testPkg[24] = {0x7e, 0x00, 0x14, 0x83, 0x56, 0x78, 0x43, 0x00, 0x01, 0x3e,
                    0xe0, 0x00, 0x40, 0x02, 0x9b, 0x02, 0x1a, 0x02, 0x05, 0x00,
                    0x00, 0x00, 0x05, 0x47};  // from datasheet

char hexTable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void setup() {
  Serial.flush();
  mySerial.begin(xBee_Baudrate);
  Serial.begin(xBee_Baudrate);
  xBee.begin(mySerial);
  while (! Serial) // wait until serial port is up and running
  { }

  delay(500); // just to be sure
}

char chksum(char *pk, int lgt)
{
  char s = 0;
  for (int i = 0; i < lgt; i++)
    s += *(pk + i);
  return s;
}

/*
void getPkg(char *package){
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
*/

void loop() {
  delay(5000);
}
