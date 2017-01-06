#include <Adafruit_NeoPixel.h>



#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "config.h"

#define DHTPIN D4
#define DHTTYPE DHT11 
#define SECONDS_DS(seconds)  ((seconds)*1000000UL)
#define PIN            5
#define STOP_PIN D2
#define NUMPIXELS      1
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long lastMsg=0;
int value =0;
const char* mqtt_server = SERVERADDRESS;
char* msg="";
char str_humidity[10], str_temperature[10];

void setup()
{
  pinMode(STOP_PIN, OUTPUT);
  digitalWrite(STOP_PIN, HIGH);
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0,0,150)); 
  pixels.show(); 
 setup_wifi();
}


void setup_wifi() {
  WiFi.begin(WIFIHOTSPOT, WIFIKEY);
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) { 
    client.publish("sannannappi", "kukkuu");
    pixels.setPixelColor(0, pixels.Color(0,150,0)); 
    pixels.show();
    delay(3000);
    pixels.setPixelColor(0, pixels.Color(0,0,0)); 
    pixels.show();
    
    digitalWrite(STOP_PIN, LOW);
    pixels.setPixelColor(0, pixels.Color(150,0,0)); 
    pixels.show();      
    } else {   
      delay(2000);
    }
  }
}

void loop() {
   if (!client.connected()) {
    reconnect();
  }
}
