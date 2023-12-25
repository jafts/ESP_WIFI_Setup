#include "wifi_setup.h"
#include "custom_web.h"

char ssid[32];
char password[64];
bool isInAPMode = false;

void setupWiFi(const char* baseSSID, const char* defaultPassword) {
    Serial.println("Attempting to connect to stored WiFi...");
    preferences.begin("wifi", false);

    size_t ssidLen = preferences.getBytes(clientModeSSIDKey, ssid, sizeof(ssid));


    preferences.getBytes(clientModeSSIDKey, ssid, sizeof(ssid));
    preferences.getBytes(clientModePasswordKey, password, sizeof(password));
    
    // If no stored client mode SSID, use the default one with MAC address
    if (ssidLen == 0) {
        Serial.println("No credentials found. Setting up default AP");
        uint8_t mac[6];
        WiFi.macAddress(mac);
        snprintf(ssid, sizeof(ssid), "%s%02X%02X%02X", baseSSID, mac[3], mac[4], mac[5]);
        strcpy(password, defaultPassword); // Use default password for AP mode
    }

    WiFi.begin(ssid, password);
    unsigned long startAttemptTime = millis();
    unsigned long runningAttemptTime = startAttemptTime;
    while (WiFi.status() != WL_CONNECTED && runningAttemptTime - startAttemptTime < 5000) {
        runningAttemptTime = millis();
        delay(500);
        Serial.print('.');
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Failed to connect, entering AP mode...");

        // Use default SSID and Password for AP mode if not already set
        uint8_t mac[6];
        WiFi.macAddress(mac);
        snprintf(ssid, sizeof(ssid), "%s%02X%02X%02X", baseSSID, mac[3], mac[4], mac[5]);

        startAPMode();
        setupWebServer();
    } else {
        Serial.println("Connected to WiFi!");
        setupWebServer();
        isInAPMode = false;
    }

    preferences.end(); // Close the preferences
}

void startAPMode() {
    WiFi.disconnect();
    delay(1000);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.println("Web server started. Connect to " + WiFi.softAPIP().toString());
}
