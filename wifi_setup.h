#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>
#include <Preferences.h>

extern char ssid[32];
extern char password[64];
extern bool isInAPMode;

void setupWiFi(const char* baseSSID, const char* defaultPassword);
void startAPMode();

#endif // WIFI_SETUP_H
