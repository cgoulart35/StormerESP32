#include "LogUtility.h"
#include "WiFiManager.h"
#include "LogServer.h"
#include "OTAUpdater.h"
#include "NotifyRun.h"

LogUtility logUtility;
WiFiManager wifiManager(logUtility);
LogServer logServer(logUtility);
OTAUpdater otaUpdater(logUtility);

TaskHandle_t heartbeatTaskHandle = NULL;
TaskHandle_t wifiManagerTaskHandle = NULL;
TaskHandle_t logServerTaskHandle = NULL;
TaskHandle_t otaTaskHandle = NULL;

void heartbeatTask(void *pvParameters) {
    while (true) {
        unsigned long currentTime = millis();       // Get the time in ms since started
        unsigned long seconds = currentTime / 1000; // Convert ms to seconds
        unsigned long minutes = seconds / 60;       // Convert seconds to minutes
        unsigned long hours = minutes / 60;         // Convert minutes to hours
        
        // Print the heartbeat message
        logUtility.loglnInfo("Heartbeat (loop running) | Uptime: " + String(hours) + "h, " + String(minutes % 6) + "m, " + String(seconds % 60) + "s");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void wifiManagerTask(void *pvParameters) {
    // Connect to Wi-Fi
    wifiManager.connect();

    while (true) {
        // Handle WiFi reconnections
        wifiManager.handle();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void logServerTask(void *pvParameters) {
    // Setup log server
    logServer.setup();

    while (true) {
        // Handle log server
        logServer.handle();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void otaUpdaterTask(void *pvParameters) {
    // Setup OTA
    otaUpdater.setup();

    while (true) {
        // Handle OTA updates
        otaUpdater.handle();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void setup() {
    // Start serial
    Serial.begin(115200);

    // Create tasks
    xTaskCreatePinnedToCore(heartbeatTask, "Heartbeat Task", 4096, NULL, 4, &heartbeatTaskHandle, 0);
    xTaskCreatePinnedToCore(wifiManagerTask, "WiFi Connection Task", 4096, NULL, 3, &wifiManagerTaskHandle, 0);
    xTaskCreatePinnedToCore(logServerTask, "Log Server Task", 4096, NULL, 2, &logServerTaskHandle, 0);
    xTaskCreatePinnedToCore(otaUpdaterTask, "OTA Updater Task", 4096, NULL, 1, &otaTaskHandle, 0);
}

void loop() {}
