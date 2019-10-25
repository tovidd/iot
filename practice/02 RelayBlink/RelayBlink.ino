int btn;
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 

char auth[] = "4ac7f3bb9093460cb63da5467118e89f";
char ssid[] = "Vocaloid_ShitDevice";
char pass[] = "reggyjr09";

BLYNK_WRITE(V0)
{
  btn= param.asInt();
}

void setup () {
  //  pinMode(motorpin2,OUTPUT);        // set pin 4 as output
  //  pinMode(obstaclePin, INPUT);        //set pin 7 as input
   Serial.begin(9600); 
   Blynk.begin(auth, ssid, pass);
   //pinMode(LED_BUILTIN, OUTPUT);        //set pin 3 as output
}

void loop () {
  Blynk.run();
  if(btn==1)
  {
    digitalWrite(LED_BUILTIN, HIGH); delay(3000);
    digitalWrite(LED_BUILTIN, LOW); delay(1000);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
