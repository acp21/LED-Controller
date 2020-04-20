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

// My animations
#include "animations/pattern.h"
#include "animations/animation.h"
#include "animations/trail.h"
// Constant defintions
#define NUM_LEDS 120
#define DATA_PIN 14

using namespace std;

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
      if(millis() - attempt >= 20000){
        Serial.println("Could not connect to Wifi, restarting");
        break;
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

  
  // FastLED.addLeds<WS2812B, 14, GRB>(ledArr, NUM_LEDS);
  // ptr = &ledArr;

  
  FastLED.addLeds<WS2812B, 14, GRB>(ledArr, NUM_LEDS);
  server.begin(); // Start server
}

Trail trail = Trail(2, 10, 3, 0, NUM_LEDS, 171, 1, 255);


// Looping leds[i-1] = x causes ESP to crash on client connect for unkown reason
// May also crash if referencing any out of bounds index, use CRGBArray instead


void loop() {
  
  // Serial.println("Loop");
  // Serial.println("Loop");
  trail.next();
  // FastLED.show();
  // trail.next();
  // *ptr[5] = CRGB::Blue;  // THIS SHOULD MAKE 5th LED turn on, however it does not
  // FastLED.show();
}