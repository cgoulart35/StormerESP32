#include "WiFiManager.h"

WiFiManager::WiFiManager(LogUtility& logUtility)
    : logUtility(logUtility), previousMillis(0), isDisconnected(true) {}

void WiFiManager::connect() {
    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    logUtility.loglnInfo("Connecting to Wi-Fi...");
}

void WiFiManager::handle() {
    unsigned long currentMillis = millis();

    // Check Wi-Fi connection and reconnect if necessary
    if (WiFi.status() != WL_CONNECTED && (currentMillis - previousMillis >= WIFI_RECONNECT_INTERVAL)) {
        logUtility.loglnInfo("Wi-Fi disconnected. Attempting reconnection...");

        // Try to reconnect to Wi-Fi
        isDisconnected = true;
        previousMillis = currentMillis;
        connect(); 

    // If reconection failed, but connected before next reattempt
    } else if (isDisconnected && WiFi.status() == WL_CONNECTED) {
        logUtility.logInfo("Wi-Fi connected! ");
        logUtility.logInfo("IP address: ");
        logUtility.loglnInfo(WiFi.localIP().toString());
        isDisconnected = false;
    }
}
