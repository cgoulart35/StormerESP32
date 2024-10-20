#include "OTAUpdater.h"

OTAUpdater::OTAUpdater(LogUtility& logUtility)
    : logUtility(logUtility), lastProgress(100) {}

void OTAUpdater::setup() {
    // Set the LED pin as output
    pinMode(LED_BUILTIN, OUTPUT);

    // Initialize OTA
    ArduinoOTA.onStart([this]() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
        logUtility.loglnInfo("Start updating " + type);
        digitalWrite(LED_BUILTIN, HIGH);
    });

    ArduinoOTA.onEnd([this]() {
        logUtility.loglnInfo("\nEnd OTA");
        digitalWrite(LED_BUILTIN, LOW);
    });

    ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
        unsigned int currentProgress = (progress * 100) / total;
        if (lastProgress != currentProgress)
            logUtility.loglnInfo("Progress: " + String(currentProgress) + "%");
        lastProgress = currentProgress;
    });

    ArduinoOTA.onError([this](ota_error_t error) {
        logUtility.loglnError("Error[" + String(error) + "]: ");
        if (error == OTA_AUTH_ERROR) {
            logUtility.loglnError("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            logUtility.loglnError("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            logUtility.loglnError("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            logUtility.loglnError("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            logUtility.loglnError("End Failed");
        }
        digitalWrite(LED_BUILTIN, LOW);
    });

    ArduinoOTA.begin();
}

void OTAUpdater::handle() {
    // Handle OTA updates
    ArduinoOTA.handle();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
