// LED-Control
// Written by Adam Pohl

#define FASTLED_ESP8266_RAW_PIN_ORDER
// Arduino include
#include <Arduino.h>
// Standard C libraries
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
// Arduino Libraries
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

using namespace std;

// Create leds object
CRGB leds[NUM_LEDS];

CRGBArray<NUM_LEDS> ledset;

AsyncWebServer server(80);

void red(){
for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB(255, 0, 255);
        leds[i] = CRGB::Red;
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(30);
        // return 0;
    }
}

void blue(){
for(int i = 0; i < NUM_LEDS; i++){
        Serial.println("Loop");
        leds[i] = CRGB(255, 0, 255);
        leds[i] = CRGB::Blue;
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(30);
    }
}

void green(){
for(int i = 0; i < NUM_LEDS; i++){
        leds[i] = CRGB(255, 0, 255);
        leds[i] = CRGB::Green;
        FastLED.show();
        leds[i] = CRGB::Black;
        delay(30);
    }
}

// Following code is needed to setup function call maps

typedef void (*FnPtr)(void);
std::map<std::string, FnPtr> myMap;



void setup() {

  Serial.begin(9600);
  
  myMap["red"] = red;
  myMap["blue"] = blue;
  myMap["green"] = green;
  
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
      if(millis() - attempt >= 20000){
        Serial.println("Could not connect to Wifi, restarting");
        ESP.restart();
      }
  }
  Serial.println();
  Serial.println("Connected to WiFi!");
  Serial.print("Local IP:");
  Serial.println(WiFi.localIP());

// On POST request with body, create a dynamic json document and save data to a json object
  server.onRequestBody([](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
    Serial.println("Received POST with body");
    if (request->url() == "/post") { // Ensure that post request is going to /post endpoint
      DynamicJsonDocument document(1024);
      deserializeJson(document, (const char*)data);
      JsonObject root = document.as<JsonObject>();
      Serial.println("-----RECEIVED JSON-----");
      serializeJsonPretty(document, Serial); // Print json to serial port
      Serial.println(); // Print empty line for styling purposes
      Serial.println("-----------------------");
      request->send(200, "text/plain", "Json object received sucessfully");
      const char * color = root["color"];
      // myMap[color](); // Line currently not working
    }
  });

  
  FastLED.addLeds<WS2812B, 14, GRB>(ledset, NUM_LEDS);
  FastLED.addLeds<WS2812B, 14, GRB>(leds, NUM_LEDS); // Add leds to leds objecct
  
  server.begin(); // Start server
}

// VERY IMPORTANT
// Looping leds[i-1] = x causes ESP to crash on client connect for some bizarre reason
// May also crash if referencing any out of bounds index, use ledsets instead

// Testing color change functions

void loop() {
  Serial.println("Looping");
  leds[3] = CRGB::Red;
}