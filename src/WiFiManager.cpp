#include "WiFiManager.h"

WiFiManager::WiFiManager(LogUtility& logUtility, const char* ssid, const char* password)
    : logUtility(logUtility), ssid(ssid), password(password) {}

void WiFiManager::connect() {
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    logUtility.log("Connecting to Wi-Fi");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        logUtility.log(".");
    }
    
    logUtility.logln(" connected!");
    logUtility.log("IP address: ");
    logUtility.logln(WiFi.localIP().toString());
}

void WiFiManager::handle() {
    // Check Wi-Fi connection and reconnect if necessary
    if (WiFi.status() != WL_CONNECTED) {
        logUtility.logln("Wi-Fi disconnected, attempting to reconnect...");
        connect(); // Try to reconnect to Wi-Fi
    }
}
