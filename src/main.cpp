// LED-Control
// Written by Adam Pohl

#define FASTLED_ESP8266_RAW_PIN_ORDER

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
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
        Serial.println("Could not connect to Wifi, restarting");
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
      const char * name = root["name"];
      Serial.println(name);
      request->send(200, "text/plain", "Json object received sucessfully");
    }
  });
  
  FastLED.addLeds<WS2812B, 14, GRB>(leds, NUM_LEDS); // Add leds to leds objecct
  
  server.begin(); // Start server
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