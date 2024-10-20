#ifndef HTTP_CLIENT_TASK_SAFE_H
#define HTTP_CLIENT_TASK_SAFE_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <LogUtility.h>

class HTTPClientTaskSafe {
public:
    HTTPClientTaskSafe(LogUtility& logUtility);
    void sendPost(const String& transactionUUID, const String& url, const String& message);

private:
    struct TaskParams {
        HTTPClientTaskSafe* httpClientTaskSafe;
        String transactionUUID;
        String url;
        String message;
    };

    LogUtility& logUtility;
    SemaphoreHandle_t httpMutex;

    static void sendPostTask(void *pvParameters);
};

#endif
