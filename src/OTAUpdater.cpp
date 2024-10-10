#include "OTAUpdater.h"

OTAUpdater::OTAUpdater(LogUtility& logUtility)
    : logUtility(logUtility) {}

void OTAUpdater::setupOTA() {
    // Initialize OTA
    ArduinoOTA.onStart([this]() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
        logUtility.logln("Start updating " + type);
    });

    ArduinoOTA.onEnd([this]() {
        logUtility.logln("\nEnd OTA");
    });

    ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
        logUtility.logln(String("Progress: %u%%\r", (progress / (total / 100))));
    });

    ArduinoOTA.onError([this](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
            logUtility.logln("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            logUtility.logln("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            logUtility.logln("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            logUtility.logln("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            logUtility.logln("End Failed");
        }
    });

    ArduinoOTA.begin();
}

void OTAUpdater::handleOTA() {
    // Handle OTA updates
    ArduinoOTA.handle();
}
