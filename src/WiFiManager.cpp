#include "WiFiManager.h"

WiFiManager::WiFiManager(LogUtility& logUtility)
    : logUtility(logUtility), previousMillis(0), isDisconnected(true) {}

void WiFiManager::connect() {
    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    logUtility.logln("Connecting to Wi-Fi...");
}

void WiFiManager::handle() {
    unsigned long currentMillis = millis();

    // Check Wi-Fi connection and reconnect if necessary
    if (WiFi.status() != WL_CONNECTED && (currentMillis - previousMillis >= WIFI_RECONNECT_INTERVAL)) {
        logUtility.logln("Wi-Fi disconnected. Attempting reconnection...");

        // Try to reconnect to Wi-Fi
        isDisconnected = true;
        previousMillis = currentMillis;
        connect(); 

    // If reconection failed, but connected before next reattempt
    } else if (isDisconnected && WiFi.status() == WL_CONNECTED) {
        logUtility.log("Wi-Fi connected! ");
        logUtility.log("IP address: ");
        logUtility.logln(WiFi.localIP().toString());
        isDisconnected = false;
    }
}
