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
#include "animations/fade.h"
#include "animations/breathe.h"

// Constant defintions
#define NUM_LEDS 120
#define DATA_PIN 14

using namespace std;

// Create webserver
AsyncWebServer server(80);

// Head of animation linked list
// Each animation will be appended in linked list
Animation head;


void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  if(!SPIFFS.begin()){
    Serial.println("SPIFFS ERROR");
    return;
  }
  Serial.println("Spiffs Mounted");

  // Get wifi credentials from json file in board memory
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

  // Used to check for WiFi timeout
  int attempt = millis();
  // Attempt to connect to WiFi
  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
      if(millis() - attempt >= 20000){
        Serial.println("Could not connect to WiFi");
      }
  }
  Serial.println();
  Serial.println("Connected to WiFi!");
  Serial.print("Local IP:");
  Serial.println(WiFi.localIP());

// On POST request with body, create a dynamic json document and save data to a json object
// Json object will contain an array of objects, each object having a string which defines its type, as well as parameters specific to that type
// Based on the type, a constructor will be called to create one of many animation objects, all of which are inherited from Animation
// These will then be added to a  linked list and looped through
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
    }
  });

  // Add leds to FastLED object
  FastLED.addLeds<WS2812B, 14, GRB>(ledArr, NUM_LEDS);
  server.begin(); // Start server
}

// Example of creating different types of animation objects | Lines unused
Trail trail = Trail(2, 10, 3, 0, NUM_LEDS, 171, 1, 255);
Fade fade = Fade(0, 15, 50, 7, 200);
Breathe breathe = Breathe(0, 15, 50, 5, CRGB::Blue);

void loop() {
  // Calls next() on head object
  // This simply calls next() on the next object in the linked list
  head.next();
}