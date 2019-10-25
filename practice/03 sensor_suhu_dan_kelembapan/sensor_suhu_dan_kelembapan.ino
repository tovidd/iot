
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG
#define LED 16 // D0
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "dht.h"
#define dht_apin 5 // D1
#define TRIGGER_PIN 12 // D6
#define ECHO_PIN 13 // D7   
dht DHT;

//char ssid[]= "Redmi";
//char pass[]= "trenggalek1998"; 
char ssid[]= "knosre";
char pass[]= "sukasuka-"; 
char auth[]= "oGGeb93mYEtx0_rEQdYMu0qciLRJK1tI";
WidgetLCD lcd(V1), lcd2(V2), lcd3(V3); 
// https://randomnerdtutorials.com/esp32-esp8266-mysql-database-php/

void setup(){
  Serial.begin(9600);
  delay(1000);
  Blynk.begin(auth, ssid, pass);
  delay(1000);
  
  lcd.clear(); 
  lcd2.clear();
  lcd3.clear(); 
  pinMode(LED, OUTPUT); 
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
} 
 
void loop(){
  delay(1000);
  DHT.read11(dht_apin);
  Serial.print(String(DHT.humidity, 2) + " RH\n" );
  Serial.print(String(DHT.temperature, 2) + " Celcius\n"); 
  digitalWrite(LED, HIGH);
  delay(2000);

//  lcd.clear(); 
//  lcd2.clear(); 
  lcd.print(0, 0, ">> * Update! *\n");
  lcd.print(0, 0, ">> " + String(DHT.humidity, 2) + " RH\n");
  lcd.print(0, 1, ">> " + String(DHT.temperature, 2) + " Celcius\n");
  digitalWrite(LED, LOW);
  delay(2000);
    
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  double duration = pulseIn(ECHO_PIN, HIGH);
  double distance= duration*0.034/2;
//  lcd3.clear(); 
  Serial.print(distance);
  Serial.println("cm");
  lcd.print(0, 0, ">> " + String(distance, 2) + " cm\n\n");
  Blynk.run();  
}
