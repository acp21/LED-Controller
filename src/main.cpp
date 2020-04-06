// LED-Control
// Written by Adam Pohl

#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <FS.h>

// Constant defintions
#define NUM_LEDS 120
#define DATA_PIN 14

// Create leds object
CRGB leds[NUM_LEDS];

AsyncWebServer server(80);


void setup() {

  Serial.begin(9600);
  
  
  if(!SPIFFS.begin()){
    Serial.println("SPIFFS ERROR");
    return;
  }
  Serial.println("Spiffs Mounted");

  const int capacity = JSON_OBJECT_SIZE(10);
  StaticJsonDocument<capacity> doc;
  File credentials = SPIFFS.open("/pass.json", "r");
  deserializeJson(doc, credentials);

  const char* ssid = doc["ssid"];
  const char* password = doc["password"];
  Serial.println(ssid);
  Serial.println(password);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  credentials.close();

  int attempt = millis();
  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
      if(millis() - attempt >= 10000){
        Serial.println("Could not connect to Wifi");
        ESP.restart();
      }
  }
  Serial.println();
  Serial.println("Connected to WiFi!");
  Serial.print("Local IP:");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Connected to LED Control");
  });

  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request){
    // Write post handler here
  });
  
  FastLED.addLeds<WS2812B, 14, GRB>(leds, NUM_LEDS);
  
  server.begin();
}

// VERY IMPORTANT
// Looping leds[i-1] = x causes ESP to crash on client connect for some bizarre reason
// May also crash if referencing any out of bounds index, use ledsets instead

 void loop() {
      for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB(255, 0, 255);
        leds[i] = CRGB::Blue;
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(30);
      }
  }