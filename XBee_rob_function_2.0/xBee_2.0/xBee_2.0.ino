//#include <Dynamixel_Serial.h>
//#include <readxBee.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   CrustCrawler PIN Setup:  Green wire to PIN 10,                                                                           //
//                            Yellow wire to PIN 11,                                                                          //
//                            Black wire to ground,                                                                           //
//                            Red wire to 3.3v,                                                                               //
//                            Blue wire to PIN2                                                                               //
//                                                                                                                            //
//          Xbee PIN Setup:   Green wire -> Rx to PIN 19,                                                                     //
//                            White1 wire -> GND to GND,                                                                      //
//                            Blue wire -> 5v to 5v,                                                                          //
//                            White2 -> RST to RST,                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int x, y, z, emg1, emg2;
int infoPk[24];
void actualName(){
  if(Serial1.available() >= 24){
    if (Serial1.read() == 0x7E){
          for (int i = 0; i < 24 ; i++){
            byte jelly = Serial1.read();
            infoPk[i] = jelly;
          }
  for(int a = 13; a < 24; a++) {
    x = infoPk[15] + (infoPk[14] << 8);
    y = infoPk[13] + (infoPk[12] << 8);
    z = infoPk[17] + (infoPk[16] << 8);
    emg1 = infoPk[11] + (infoPk[10] << 8);
    emg2 = infoPk[19] + (infoPk[18] << 8);
   }
    Serial.print(" X = ") && Serial.print(x);
    Serial.print(" Y = ") && Serial.print(y);
    Serial.print(" Z = ") && Serial.print(z);
    Serial.print(" EMG Ch.1 = ") && Serial.print(emg1);
    Serial.print(" EMG Ch.2 = ") && Serial.print(emg2);
    Serial.println();
  }
 }
}
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  actualName();
}
