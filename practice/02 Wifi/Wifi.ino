 #include <ESP8266WiFi.h>
 #include <WiFiClient.h>  

 const char* ssid     = "14305"; //SSID
 const char* password = "Sampurasun712"; //Password
 WiFiClient client;  

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop(){}
 

