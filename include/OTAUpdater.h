#ifndef OTAUPDATER_H
#define OTAUPDATER_H

#include <ArduinoOTA.h>
#include <LogUtility.h>

class OTAUpdater {
public:
    OTAUpdater(LogUtility& logUtility);
    void setup();
    void handle();
    
private:
    LogUtility& logUtility;

    void setupLedPins();
};

#endif
