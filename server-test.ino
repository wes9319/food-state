/*  ----------------------------------------------------------------
    www.prometec.net
    Prog_75_1
    
    Encendiendo y apagando LEDs desde Arduino y un navegador web
    Y el modulo WIFI ESP8266
    http://www.prometec.net/esp8266/
--------------------------------------------------------------------  
*/


#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX

String W =" ";
char w ;

void setup()
   { 
     Serial.begin(9600);
     BT1.begin(9600); 
     pinMode(13, OUTPUT);
   }

void loop()
   { 
     if (BT1.available())        // Lo que entra por WIFI - Serial
         { w = BT1.read() ;
           Serial.print(w);      // Vamos montando un String con lo que entra
           W = W + w ;
         }
     if (Serial.available())    // Lo que entra por Serial - WIFI
          {  char s = Serial.read();
             BT1.print(s);
          }
    if ( w == '\n')                     // Sin han pulsado intro
       { if ( W.indexOf("P13") > 0 )    // Si P13 esta incluido en el string
             { digitalWrite( 13, !digitalRead(13)) ;   
               Serial.println("Invirtiendo pin 13");
             }
         
         W = "" ;  w = ' ' ;    
       }
}


