#ifndef NOTIFY_RUN_H
#define NOTIFY_RUN_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LogUtility.h>

class NotifyRun {
public:
    NotifyRun(LogUtility& logUtility, const String& channelId);
    int publish(const String& message);

private:
    LogUtility& logUtility;
    String channelId;
};

#endif // NOTIFY_RUN_H
