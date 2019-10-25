#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>
#include <BlynkSimpleEsp8266.h>

//Inisialisasi untuk Ultrasonic sensor
const int trigPin = D1;
const int echoPin = D2;
long duration;
int distance;

char ssid[]= "knosre";
char pass[] = "sukasuka";

int status = WL_IDLE_STATUS;
WiFiClient client; 

//dht11
#include "dht.h"
#define dht_apin D4 // Analog Pin sensor is connected to
dht DHT;

//buzzer 
const int buttonPin= D6;
const int buzzerPin= D7; 
int buttonState= 0; 

//tweet
#include <WiFiServer.h>
#include <WiFiUdp.h>
String API = "IM7HHQR7WPHV0SOS";
String tweet = "Hello world. @esp8266";




//Inisialisasi untuk ThingSpeak
unsigned long myChannelNumber = 726575;
const char * myWriteAPIKey = "CDLNWSYM9BPQPX2Y";
//const char * myReadAPIKey = "MSKCYX820985L84H";
const int fieldNumber = 1; //field number yang akan di isi dengan data

void setup() 
{                
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input    
  Serial.begin(9600); 
  delay(100);

  //buzzer
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, pass);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());

  //Memulai koneksi dengan ThingSpeak server
  ThingSpeak.begin(client);
}

void loop()
{
  buttonRead();
  readUltrasonicSensor();
  suhuKelembapan();
}

void sendThingSpeakData(int distance)
{
  ThingSpeak.writeField(myChannelNumber, fieldNumber, distance, myWriteAPIKey); 
  delay (1000); //Free user hanya bisa mengupdate setiap 15 detik
}

void sendThingSpeakData2(int humidity)
{
  ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey); 
  delay (1000); //Free user hanya bisa mengupdate setiap 15 detik
}

void sendThingSpeakData3(int temperature)
{
  ThingSpeak.writeField(myChannelNumber, 3, temperature, myWriteAPIKey); 
  delay (1000); //Free user hanya bisa mengupdate setiap 15 detik
}

void readUltrasonicSensor()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  sendThingSpeakData(distance);
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

    sendThingSpeakData2(DHT.humidity);
    sendThingSpeakData3(DHT.temperature);
}

void buzzerOn()
{
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
}

void buttonRead() //button+buzzer+tweet
{
  buttonState= digitalRead(buttonPin);
  if(buttonState == LOW)
  {
    //Serial.println("Button Pressed");
    //Blynk.notify("Button is pressed");
    //Blynk.email("toviddd@gmail.com", "hi from blynk and arduino", "Ilham / 16070, Tofid/16070");
    client.print("GET /apps/thingtweet/1/statuses/update?key=" + API + "&status=" + tweet + " HTTP/1.1\r\n");
    client.print("Host: api.thingspeak.com\r\n");
    client.print("Accept: */*\r\n");
    client.print("User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n");
    client.print("\r\n");
    buzzerOn();
  }
}
