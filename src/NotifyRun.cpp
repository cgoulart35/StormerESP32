#include "NotifyRun.h"

NotifyRun::NotifyRun(LogUtility& logUtility, HTTPClientTaskSafe& httpClientTaskSafe)
    : logUtility(logUtility), httpClientTaskSafe(httpClientTaskSafe) {}

void NotifyRun::publish(const String& transactionUUID, const String& channelId, const String& message) {
    // create a new task for publishing the message
    TaskParams* params = new TaskParams{this, transactionUUID, channelId, message};
    xTaskCreatePinnedToCore(notifyRunTask, "Notify Run Task", 4096, params, 2, NULL, 0);
}

void NotifyRun::notifyRunTask(void *pvParameters) {
    TaskParams* params = (TaskParams*)pvParameters;
    NotifyRun* notifyRun = params->notifyRun;

    String transactionUUID = params->transactionUUID;
    String channelId = params->channelId;
    String message = params->message;
    String url = "https://notify.run/" + channelId;

    notifyRun->logUtility.loglnInfoTransactionID(transactionUUID, "Publishing message to channel " + channelId + ": " + message);
    notifyRun->httpClientTaskSafe.sendPost(transactionUUID, url, message);

    // delete the task once done
    vTaskDelete(NULL);
}
