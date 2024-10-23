#include "TaskInfo.h"
#include "LogUtility.h"
#include "HTTPClientTaskSafe.h"
#include "NotifyRun.h"
#include "WiFiManager.h"
#include "LogServer.h"
#include "OTAUpdater.h"
#include "ActivitySense.h"

LogUtility logUtility;
HTTPClientTaskSafe httpClientTaskSafe(logUtility);
NotifyRun notifyRun(logUtility, httpClientTaskSafe);

WiFiManager wifiManager(logUtility);
LogServer logServer(logUtility);
OTAUpdater otaUpdater(logUtility);
ActivitySense activitySense(logUtility, notifyRun);

TaskInfo taskInfo;
TaskHandle_t heartbeatTaskHandle = NULL;
TaskHandle_t wifiManagerTaskHandle = NULL;
TaskHandle_t logServerTaskHandle = NULL;
TaskHandle_t otaTaskHandle = NULL;
TaskHandle_t activitySenseTaskHandle = NULL;

void heartbeatTask(void *pvParameters) {
    while (true) {
        unsigned long currentTime = millis();       // Get the time in ms since started
        unsigned long seconds = currentTime / 1000; // Convert ms to seconds
        unsigned long minutes = seconds / 60;       // Convert seconds to minutes
        unsigned long hours = minutes / 60;         // Convert minutes to hours
        
        // Print the heartbeat message
        logUtility.loglnInfo("Heartbeat (loop running) | Uptime: " + String(hours) + "h, " + String(minutes % 60) + "m, " + String(seconds % 60) + "s");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void wifiManagerTask(void *pvParameters) {
    // Connect to Wi-Fi
    wifiManager.connect();

    while (true) {
        // Handle WiFi reconnections
        wifiManager.handle();
    }
}

void logServerTask(void *pvParameters) {
    // Setup log server
    logServer.setup();

    while (true) {
        // Handle log server
        logServer.handle();
    }
}

void otaUpdaterTask(void *pvParameters) {
    // Setup OTA
    otaUpdater.setup();

    while (true) {
        // Handle OTA updates
        otaUpdater.handle();
    }
}

void activitySenseTask(void *pvParameters) {
    // Setup activity sense
    activitySense.setup();

    while (true) {
        // Handle activity
        activitySense.handle();
    }
}

void setup() {
    // Start serial
    Serial.begin(115200);

    // Create tasks
    if (ENABLE_HEARTBEAT_LOG)
        xTaskCreatePinnedToCore(heartbeatTask, "Heartbeat Task", 4096, NULL, taskInfo.getPriority("Heartbeat Task"), &heartbeatTaskHandle, taskInfo.getCore("Heartbeat Task"));
    xTaskCreatePinnedToCore(wifiManagerTask, "WiFi Connection Task", 4096, NULL, taskInfo.getPriority("WiFi Connection Task"), &wifiManagerTaskHandle, taskInfo.getCore("WiFi Connection Task"));
    if (ENABLE_LOG_SERVER)
        xTaskCreatePinnedToCore(logServerTask, "Log Server Task", 4096, NULL, taskInfo.getPriority("Log Server Task"), &logServerTaskHandle, taskInfo.getCore("Log Server Task"));
    xTaskCreatePinnedToCore(otaUpdaterTask, "OTA Updater Task", 4096, NULL, taskInfo.getPriority("OTA Updater Task"), &otaTaskHandle, taskInfo.getCore("OTA Updater Task"));
    if (ENABLE_ACTIVITY_SENSE)
        xTaskCreatePinnedToCore(activitySenseTask, "Activity Sense Task", 4096, NULL, taskInfo.getPriority("Activity Sense Task"), &activitySenseTaskHandle, taskInfo.getCore("Activity Sense Task"));
}

void loop() {}
