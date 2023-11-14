#ifndef CUSTOM_WEB_H
#define CUSTOM_WEB_H

#include <WebServer.h>
#include <Preferences.h>

extern WebServer server;
extern Preferences preferences;
extern char ssid[32];    // Max SSID length is 32 bytes
extern char password[64]; // Max WPA2 password length is 63 bytes
String getHTML(); 
void setupWebServer(); 

#endif // CUSTOM_WEB_H
