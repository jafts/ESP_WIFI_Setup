#include "wifi_setup.h"
#include "custom_web.h"
#include <SPIFFS.h> 

WebServer server(80);
Preferences preferences;

void setupWebServer() {
    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Serve the HTML page from SPIFFS when the root route is accessed
    server.on("/", HTTP_GET, [](){ 
        File file = SPIFFS.open("/wifi.htm", "r");
        if (!file) {
            Serial.println("Failed to open file for reading");
            server.send(404, "text/plain", "404: File Not Found");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    // Handle form submission and save credentials
    server.on("/submit", HTTP_GET, []() {
        String receivedSSID = server.arg("ssid");
        String receivedPassword = server.arg("password");
        
        receivedSSID.toCharArray(ssid, sizeof(ssid));
        receivedPassword.toCharArray(password, sizeof(password));
        
        preferences.begin("wifi", false);
        preferences.putBytes(clientModeSSIDKey, ssid, strlen(ssid) + 1); // Use client mode keys
        preferences.putBytes(clientModePasswordKey, password, strlen(password) + 1);
        delay(1000);        
        preferences.end();  // Close the preferences

        server.send(200, "text/plain", "Credentials Saved! Rebooting...");
        delay(1000);
        ESP.restart();
    });

    server.on("/clearprefs", HTTP_GET, []() {
        clearPreferences();
        server.send(200, "text/plain", "Preferences cleared. Please restart the device.");
        ESP.restart();
    });


    server.begin();
}

void clearPreferences() {
    Serial.println("Factory Resetting...");
    preferences.begin("wifi", false);
    preferences.clear();
    preferences.end(); 
}
