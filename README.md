# ESP_WIFI_Setup
Easy WiFi setup for AP or Client mode

This is intended  as a base for ESP web projects that continue working regardless of rather Internet or a network is available.

When the ESP fires up, it tries to connect to a network using saved credentials stored in the onboard Preferences, if there are any.

If there are no stored credentials or it is unable to connect using stored credentials, start up APMode and serve up a web page for entering wifi credentials if desired.

The default AP SSID is 'ESP32-AP-' plus the last 3 bytes of its MAC Address.

The default AP Password is '123456789' which can be modified in the .ino as defaultPassword.

The default address for accessing the web server after connecting to its Access Point is 192.168.4.1

If the ESP is able to connect to a network, you will need to locate its IP by reading it from the serial console, logging into your local router, or as I like to do by outputting to an OLED screen added to the project.

This base can easily be modified to serve up additional custom web pages using SPIFFS for your project.





