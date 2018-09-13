/*  ----------------------------------------------------------------
    http://www.prometec.net/
    Prog_76_2
    
    Montando un servidor Web en WIFI mediante
    un WIFI ESP8266 y comandos AT  
    http://www.prometec.net/servidor-web-esp8266
--------------------------------------------------------------------  
*/

#include <SoftwareSerial.h>
#define DEBUG true
 SoftwareSerial Serial3(3,2);
 //SoftwareSerial bt(10,11);
 int val=0;

String ordenes[]=
    {  //"AT+RST",
       "AT+CWMODE=3",
       //"AT+CIFSR" ,
       "AT+CIPMUX=1",
       "AT+CIPSERVER=1,80",
       "END"				// Para reconocer el fin de los comandos AT
    };

void setup()
{   Serial3.begin(9600);
    Serial.begin(9600); 
    //bt.begin(9600);
    delay (1000);
    int index = 0;
    while(ordenes[index] != "END")
        {  Serial3.println(ordenes[index++]);
        delay(1000);
           while ( true)
             {   
              String s = GetLineWIFI();
                 if ( s!= "") Serial.println(s);
                 if ( s.startsWith("no change"))   
                         break;
                 if ( s.startsWith("OK"))   
                         break;
                 if ( s.startsWith("ready"))   
                         break;
                // if (millis()-T >10000) break;  
             }
          Serial.println("....................");
      } 
}
void loop() 
{  while (Serial3.available() >0 )
    {  char c = Serial3.read();
       if (c == 71) 
          {   Serial.println("Enviada Web Request");
              webserver();
              delay(500);
          }
   }
   
   
}

void http(String output)
{
    Serial3.print("AT+CIPSEND=0,");              // AT+CIPSEND=0, num
    Serial3.println(output.length());
    if (Serial3.find(">"))                       // Si recibimos la peticion del mensaje
       {    Serial.println(output);
            Serial3.println(output);            //Aqui va el string hacia el WIFI 
            delay(10);
            while ( Serial3.available() > 0 ) 
              { if (  Serial3.find("SEND OK") )    // Busca el OK en la respuesta del wifi
                      break; 
              }
       }
}
void webserver(void) 
    {    http("<!DOCTYPE HTML>");
         http("<html>");
         http("<head><title>Proyecto Final WAN</title>");
         http("<meta http-equiv=\"refresh\" content=\"4\"><style>th, td{border: 1px solid black;} table{ border: 1px solid black; width:100%} body{ background-color:#FBFBEF; font-family:verdana; }h1{ text-align:center; color:#8A0808;} h2,h3{ text-align:center; } p{text-align: justify;} </style></head>");
         http("<body><h1>Universidad de las Americas</h1><h2>Proyecto Final Conectividad WAN</h2><h3>Sistema de Control de Alimentos Organicos</h3>");
  
         /*for (int analogChannel = 0; analogChannel < 6; analogChannel++) 
         {
            int sensorReading = analogRead(analogChannel);
            http("analog input ");
            http( String(analogChannel));
            http(" is ");
            http(String(sensorReading));
            http("<br />");
          }*/
          
        http("<p>A continuacion se mostraran los dispositivos conectados y desconectados con el actual estado del alimentos que esten controlando</p>");
        
        http("<table><tr><th>Dispositivo</th><th>ON/OFF</th> <th>Estado</th></tr>");
        http("<tr><td>1</td><td>ON</td><td>");
        val++;
        http(String(val));
        http("</td></tr>");
        http("<tr><td>2</td><td>OFF</td><td>-</td></tr>");
        http("<tr><td>3</td><td>OFF</td><td>-</td></tr>");
        http("</table>");
        http("</body></html>");
        http("");

       delay(1);
       Serial3.println("AT+CIPCLOSE=0");
       //delay(500);
    }
String GetLineWIFI()
   {   String S = "" ;
       if (Serial3.available())
          {    char c = Serial3.read(); ;
                while ( c != '\n' )            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = Serial3.read();
                   }
                 return( S ) ;
          }
   }

 /*String SerialCommand() {
  char c;
  String string="";
  while (c!='\n') {
     c = bt.read();
     if (c!=-1) {
      string+=c;
     }
    delayMicroseconds(500);
  }
  return string;
}*/


