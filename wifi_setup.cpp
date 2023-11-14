#include "wifi_setup.h"
#include "custom_web.h"

bool isInAPMode = false;

void setupWiFi(const char* baseSSID, const char* defaultPassword) {
    uint8_t mac[6];
    WiFi.macAddress(mac);
    snprintf(ssid, sizeof(ssid), "%s%02X%02X%02X", baseSSID, mac[3], mac[4], mac[5]);

    preferences.begin("wifi", false);
    size_t ssidLen = preferences.getBytes("ssid", ssid, sizeof(ssid));
    size_t passwordLen = preferences.getBytes("password", password, sizeof(password));

    if (ssidLen == 0) {
        //strcpy(ssid, defaultSSID);
        strcpy(password, defaultPassword);
    }

    WiFi.begin(ssid, password);
    unsigned long startAttemptTime = millis();
  
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nFailed to connect to WiFi. Entering AP mode.");
        startAPMode();
        setupWebServer();
    } else {
        setupWebServer();
        Serial.println("\nConnected to WiFi");
        Serial.println("Web server started. Connect to " + WiFi.localIP().toString());
        isInAPMode = false;
    }
}

void startAPMode() {
    WiFi.disconnect();
    delay(1000);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.println("Web server started. Connect to " + WiFi.softAPIP().toString());
}
