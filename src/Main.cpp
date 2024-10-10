#include <Arduino.h>
#include <WebServer.h>
#include "LogUtility.h"
#include "WiFiManager.h"
#include "OTAUpdater.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

LogUtility logUtility;
WiFiManager wifiManager(logUtility, ssid, password);
OTAUpdater otaUpdater(logUtility);

void heartbeat();

void setup() {
    // Wait to start for 10 seconds
    delay(10000);
    Serial.begin(115200);

    // Connect to Wi-Fi
    wifiManager.connect();

    // Start log server
    logUtility.startLogServer();

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
    unsigned long currentTime = millis();  // Get the time in milliseconds since the program started
    unsigned long seconds = currentTime / 1000;  // Convert milliseconds to seconds
    unsigned long minutes = seconds / 60;  // Convert seconds to minutes
    unsigned long hours = minutes / 60;  // Convert minutes to hours

    // Print the heartbeat message
    logUtility.log("Heartbeat (loop running) | Uptime: ");
    logUtility.log(String(hours));
    logUtility.log(" hours, ");
    logUtility.log(String(minutes % 60));
    logUtility.log(" minutes, ");
    logUtility.log(String(seconds % 60));
    logUtility.logln(" seconds");

    // Wait for 1 second
    delay(1000);
}