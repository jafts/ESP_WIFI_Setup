#include <Arduino.h>
#include <SPIFFS.h>
#include "wifi_setup.h"
#include "custom_web.h"

void setup() {    
  Serial.begin(115200);
  // Setup WiFi with a base SSID and a default password
  const char* baseSSID = "ESP32-AP-";
  const char* defaultPassword = "123456789";
  setupWiFi(baseSSID, defaultPassword);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED && !isInAPMode) {
    startAPMode();
    isInAPMode = true;
  }
  server.handleClient();
}
