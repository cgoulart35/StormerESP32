#include "OTAUpdater.h"

OTAUpdater::OTAUpdater(LogUtility& logUtility)
    : logUtility(logUtility) {}

void OTAUpdater::setupOTA() {
    // Initialize OTA
    ArduinoOTA.onStart([this]() {
        String type = (ArduinoOTA.getCommand() == U_FLASH) ? "sketch" : "filesystem";
        logUtility.loglnInfo("Start updating " + type);
    });

    ArduinoOTA.onEnd([this]() {
        logUtility.loglnInfo("\nEnd OTA");
    });

    ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
        logUtility.loglnInfo("Progress: " + String((progress * 100) / total) + "%");
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
    });

    ArduinoOTA.begin();
}

void OTAUpdater::handleOTA() {
    // Handle OTA updates
    ArduinoOTA.handle();
}
