#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//ultrasonik
#define TRIGGERPIN D1
#define ECHOPIN D2
WidgetLCD lcd(V1), lcd2(V2);

//suhu dan kelembapan
#include "dht.h"
#define dht_apin D4 // Analog Pin sensor is connected to
dht DHT;
WidgetLCD lcd3(V3), lcd4(V4);

//buzzer
const int buttonPin= D6;
const int buzzerPin= D7; 
int buttonState= 0; 

//conn
char auth[]= "a7708d2f572b49d68033b1937ef4ba22";
char ssid[]= "Vocaloid_ShitDevice";
char pass[] = "reggyjr09";

void setup() {
  Serial.begin(9600);
  delay(500);
  Blynk.begin(auth, ssid, pass);
  
  //ultrasonik
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  lcd.clear();
  lcd2.clear();
  lcd.print(0, 0, "Distance in centimeters(start) ");
  lcd2.print(0, 0, "alert (start) ");
  
  //suhu kelembapan
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  lcd3.clear(); 
  lcd4.clear();
  
  //buzzer
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  Blynk.run();
  ultrasonik();
  buttonRead();
  suhuKelembapan();
}

void buzzerOn()
{
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

void buttonRead() //button+buzzer
{
  buttonState= digitalRead(buttonPin);
  if(buttonState == LOW)
  {
    Serial.println("Button Pressed");
    Blynk.notify("Button is pressed");
    //Blynk.email("toviddd@gmail.com", "hi from blynk and arduino", "Ilham / 16070, Tofid/16070");
    buzzerOn();
  }
}

void ultrasonik()
{
    delay(1500);
    lcd.clear();
    lcd2.clear();
    lcd.print(0, 0, "Distance in centimeters: ");
    long duration, distance;
    digitalWrite(TRIGGERPIN, LOW);
    delayMicroseconds(3); 
    digitalWrite(TRIGGERPIN, HIGH);
    delayMicroseconds(12);
    digitalWrite(TRIGGERPIN, LOW);
    duration= pulseIn(ECHOPIN, HIGH);
    distance= (duration/2) / 29.1; 
    if(distance>7) {
      //tone(buzzerPin, 1000, 250);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
    }
    else {
      //tone(buzzerPin, 1000, 10);
      //digitalWrite(buzzerPin, HIGH);
    }
    lcd.print(7, 1, distance); 
    if(duration>5000)
    {
      lcd2.print(0, 0,"Intruder Alert!!!");
    }
    Serial.print(distance);
    Serial.println(" Cm");
}

void suhuKelembapan()
{
    DHT.read11(dht_apin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    delay(1000);//Wait 5 seconds before accessing sensor again.
    lcd3.clear(); 
    lcd4.clear(); 
    lcd3.print(0, 0, "Current Humidity = ");
    lcd3.print(7, 1, DHT.humidity);
    lcd4.print(0, 0, "Current Temperature = ");
    lcd4.print(7, 1, DHT.temperature);
}
