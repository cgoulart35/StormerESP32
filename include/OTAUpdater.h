#ifndef OTAUPDATER_H
#define OTAUPDATER_H

#include <ArduinoOTA.h>
#include <LogUtility.h>

class OTAUpdater {
public:
    OTAUpdater(LogUtility& logUtility);
    void setupOTA();
    void handleOTA();
    
private:
    LogUtility& logUtility;

    void setupLedPins();
};

#endif
