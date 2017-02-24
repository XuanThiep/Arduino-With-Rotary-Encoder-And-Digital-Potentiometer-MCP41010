#include <SPI.h>

 #define pinA  3 // Connected to CLK on KY-040
 #define pinB  4 // Connected to DT on KY-040
 #define CS    5

 
 int encoderPosCount = 128; 
 unsigned char pinALast,aVal;  

void MCP41010Write(unsigned char value);

 void setup() 
 { 
   pinMode (pinA,INPUT);
   pinMode (pinB,INPUT);
   pinMode (CS,OUTPUT);

   pinALast = digitalRead(pinA);   
   Serial.begin (115200);
   SPI.begin();
 } 

 void loop()
 { 
   aVal = digitalRead(pinA);
   if (aVal != pinALast)
   { 
     if (digitalRead(pinB) != aVal) 
     { 
       encoderPosCount ++;
       if(encoderPosCount>255)
       {
        encoderPosCount=255;
       }
     } 
     else
     {
       encoderPosCount--;
       if(encoderPosCount<0)
       {
        encoderPosCount=0;
       }
     }
     MCP41010Write((unsigned char)encoderPosCount);
     Serial.println(encoderPosCount);
   } 
   pinALast = aVal;
 } 

 void MCP41010Write(unsigned char value)
 {
   digitalWrite(CS,LOW);
   SPI.transfer(B00010001);
   SPI.transfer(value);
   digitalWrite(CS,HIGH);
 }

