#ifndef ACTIVITY_SENSE_H
#define ACTIVITY_SENSE_H

#include <LogUtility.h>
#include <NotifyRun.h>

class ActivitySense {
public:
    ActivitySense(LogUtility& logUtility, NotifyRun& notifyRun);
    void setup();
    void handle();
    
private:
    LogUtility& logUtility;
    NotifyRun& notifyRun;
    unsigned long duration;
    float distance;
    boolean buzzerState;

    void simpleBuzzerToggle();
    void complexBuzzerSong();
};

#endif
