#include <Arduino.h>
#include <WebServer.h>
#include "LogUtility.h"
#include "WiFiManager.h"
#include "OTAUpdater.h"

LogUtility logUtility;
WiFiManager wifiManager(logUtility);
OTAUpdater otaUpdater(logUtility);

void heartbeat();

void setup() {
    // Start serial
    Serial.begin(115200);

    // Connect to Wi-Fi
    wifiManager.connect();

    // Setup log utility
    logUtility.setup();

    // Setup OTA
    otaUpdater.setupOTA();
}

void loop() {
    // Handle WiFi reconnections
    wifiManager.handle();

    // Handle log server
    logUtility.handle();

    // Handle OTA updates
    otaUpdater.handleOTA();

    // Heartbeat
    heartbeat();
}

void heartbeat() {
    unsigned long currentTime = millis();       // Get the time in milliseconds since the program started
    unsigned long seconds = currentTime / 1000; // Convert milliseconds to seconds
    unsigned long minutes = seconds / 60;       // Convert seconds to minutes
    unsigned long hours = minutes / 60;         // Convert minutes to hours

    // Print the heartbeat message
    logUtility.logInfo("Heartbeat (loop running) | Uptime: ");
    logUtility.logInfo(String(hours));
    logUtility.logInfo("h, ");
    logUtility.logInfo(String(minutes % 60));
    logUtility.logInfo("m, ");
    logUtility.logInfo(String(seconds % 60));
    logUtility.loglnInfo("s");

    // Wait for 1 second
    delay(1000);
}