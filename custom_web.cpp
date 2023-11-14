#include "custom_web.h"

WebServer server(80);
Preferences preferences;

char ssid[32];
char password[64];

String getHTML() {
    String html = "<html><body>";
    html += "<form action='/submit'>";
    html += "SSID: <input type='text' name='ssid'><br>";
    html += "Password: <input type='password' name='password'><br>";
    html += "<input type='submit' value='Save'>";
    html += "</form></body></html>";
    return html;
}

void setupWebServer() {
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", getHTML());
    });

    server.on("/submit", HTTP_GET, []() {
        String receivedSSID = server.arg("ssid");
        String receivedPassword = server.arg("password");
        receivedSSID.toCharArray(ssid, sizeof(ssid));
        receivedPassword.toCharArray(password, sizeof(password));
        preferences.putBytes("ssid", ssid, strlen(ssid) + 1);
        preferences.putBytes("password", password, strlen(password) + 1);
        server.send(200, "text/plain", "Credentials Saved! Rebooting...");
        delay(3000);
        ESP.restart();
    });

    server.begin();
}
