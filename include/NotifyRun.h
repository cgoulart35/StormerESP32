#ifndef NOTIFY_RUN_H
#define NOTIFY_RUN_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <LogUtility.h>
#include "HTTPClientTaskSafe.h"

class NotifyRun {
public:
    NotifyRun(LogUtility& logUtility, HTTPClientTaskSafe& httpClientTaskSafe);
    void publish(const String& transactionUUID, const String& channelId, const String& message);

private:
    struct TaskParams {
        NotifyRun* notifyRun;
        String transactionUUID;
        String channelId;
        String message;
    };

    LogUtility& logUtility;
    HTTPClientTaskSafe& httpClientTaskSafe;

    static void notifyRunTask(void *pvParameters);
};

#endif
