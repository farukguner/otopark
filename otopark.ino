#include <RFID.h>
#include <SPI.h>
#include <Servo.h>  // servo library

#define SS_PIN 10
#define RST_PIN 9
Servo servo1;

RFID rfid(SS_PIN,RST_PIN);
 
 
int serNum[5];
 
int cards[][5] = {
  {209,99,75,43,210}, // card 1
  {172,30,239,85,8} // card 2
};
 
bool access = false;
 
void setup(){
    pinMode(3,OUTPUT);
    pinMode(2,OUTPUT);
    Serial.begin(9600);
    SPI.begin();
    rfid.init();
    servo1.attach(4);//servo motor pin
}
 
void loop(){
    
    if(rfid.isCard()){
    Serial.println("hoşgeldiniz");
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(",");
            Serial.print(rfid.serNum[1]);
            Serial.print(",");
            Serial.print(rfid.serNum[2]);
            Serial.print(",");
            Serial.print(rfid.serNum[3]);
            Serial.print(",");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
           
        }
        
       if(access){
          Serial.println("Welcome!"); 
          servo1.write(20);
          digitalWrite(3,HIGH);
          delay(5000);
          digitalWrite(3,LOW);
          servo1.write(90);  
       } else {
          Serial.println("Not allowed!");  
          digitalWrite(2,HIGH);
          delay(5000);
          digitalWrite(2,LOW);
         }        
    }  
    rfid.halt(); 
}
 
