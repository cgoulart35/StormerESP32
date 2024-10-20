#ifndef OTA_UPDATER_H
#define OTA_UPDATER_H

#include <ArduinoOTA.h>
#include <LogUtility.h>

class OTAUpdater {
public:
    OTAUpdater(LogUtility& logUtility);
    void setup();
    void handle();
    
private:
    LogUtility& logUtility;
    unsigned int lastProgress;
};

#endif
