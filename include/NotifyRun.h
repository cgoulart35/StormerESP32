#ifndef NOTIFY_RUN_H
#define NOTIFY_RUN_H

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

    TaskInfo taskInfo;
    LogUtility& logUtility;
    HTTPClientTaskSafe& httpClientTaskSafe;

    static void notifyRunTask(void *pvParameters);
};

#endif
