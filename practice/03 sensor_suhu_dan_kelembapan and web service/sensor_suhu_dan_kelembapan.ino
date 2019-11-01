#define BLYNK_PRINT Serial
#define BLYNK_DEBUG
#define LED 16 // D0
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "dht.h"
#define dht_apin 5 // D1
#define TRIGGER_PIN 12 // D6
#define ECHO_PIN 13 // D7   
dht DHT;
char ssid[]= "knosre";
char pass[]= "sukasuka-"; 
char auth[]= "oGGeb93mYEtx0_rEQdYMu0qciLRJK1tI";
double humidity, temperature, distance= 0;
WiFiClient client;
WidgetLCD lcd(V1); 
// https://circuits4you.com/2018/03/10/esp8266-nodemcu-post-request-data-to-website/

void setup(){
  Serial.begin(9600);
  delay(1000);
  Blynk.begin(auth, ssid, pass);
  delay(1000);
  lcd.clear(); 
  pinMode(LED, OUTPUT); 
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
} 
 
void loop(){
  delay(1);
  DHT.read11(dht_apin);
  humidity= DHT.humidity;
  temperature= DHT.temperature;
  Serial.print(String(humidity, 2) + " RH\n" );
  Serial.print(String(temperature, 0) + " Celcius\n"); 
  digitalWrite(LED, HIGH);
  delay(1); 
  lcd.print(0, 0, ">> * Update! *\n");
  lcd.print(0, 0, ">> " + String(humidity, 2) + " RH\n");
  lcd.print(0, 1, ">> " + String(temperature, 2) + " Celcius\n");
  digitalWrite(LED, LOW);
  delay(1); 
    
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  double duration = pulseIn(ECHO_PIN, HIGH);
  distance= duration*0.034/2;
  Serial.print(distance);
  Serial.println("cm");
  lcd.print(0, 0, ">> " + String(distance, 2) + " cm\n\n");
  String data= "humidity=" +String(humidity) +"&temperature=" +String(temperature) +"&distance=" +String(distance);
  post(data);
  delay(10000);
  Blynk.run();
}

void post(String data)
{
  HTTPClient http;
  http.begin("http://192.168.43.104:8000/api/sensorData");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode= http.POST(data);
  String response= http.getString();
  Serial.println(httpCode);
  Serial.println(response);
  http.end();
}
