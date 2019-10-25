#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[]= "a7708d2f572b49d68033b1937ef4ba22";
char ssid[]= "Vocaloid_ShitDevice";
char pass[] = "reggyjr09";
const int buttonPin= D5;
const int buzzerPin= D6;
int buttonState= 0;
void buzzerOn()
{
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

void buttonRead()
{
  buttonState= digitalRead(buttonPin);
  if(buttonState == LOW)
  {
    Serial.println("Button Pressed");
    //Blynk.notify("Button is pressed");
    Blynk.email("toviddd@gmail.com", "hi from blynk and arduino", "Ilham / 16070, Tofid/16070");
    buzzerOn();
  }
}
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  buttonRead();

}
