#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>
#include <Preferences.h>

// Define keys for storing credentials
const char* const clientModeSSIDKey = "client_ssid";
const char* const clientModePasswordKey = "client_password";
const char* const apModeSSIDKey = "ap_ssid";
const char* const apModePasswordKey = "ap_password";

extern char ssid[32];    // Max SSID length is 32 bytes
extern char password[64]; // Max WPA2 password length is 63 bytes
extern bool isInAPMode;

void setupWiFi(const char* baseSSID, const char* defaultPassword);
void startAPMode();

#endif // WIFI_SETUP_H
