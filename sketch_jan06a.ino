#include <SPI.h>

 #define pinA  3 // Pin 3 of Arduino connect to CLK on KY-040
 #define pinB  4 // Pin 4 of Arduino connect to DT on KY-040

 #define CS    5 // CS Pin of MCP41010 connect to pin 5 of Arduino
				 // SCK Pin of MCP41010 connect to pin 13 of Arduino
				 // SI Pin of MCP41010 connect to pin 11 of Arduino
				 

 
 int encoderPosCount = 128; 
 unsigned char pinALast,aVal;  

void MCP41010Write(unsigned char value);

 void setup() 
 { 
   pinMode (pinA,INPUT);
   pinMode (pinB,INPUT);
   pinMode (CS,OUTPUT);

   pinALast = digitalRead(pinA);   
   Serial.begin (115200); //baud rate = 115200, 8 bit data, 1 bit stop, no parity bit
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

