#include "HTTPClientTaskSafe.h"

HTTPClientTaskSafe::HTTPClientTaskSafe(LogUtility& logUtility)
    : logUtility(logUtility) {
        httpMutex = xSemaphoreCreateMutex();
    }

void HTTPClientTaskSafe::sendPost(const String& transactionUUID, const String& url, const String& message) {
    // create a new task for publishing the message
    TaskParams* params = new TaskParams{this, transactionUUID, url, message};
    xTaskCreatePinnedToCore(sendPostTask, "Send Post Task", 4096, params, 2, NULL, 0);
}

void HTTPClientTaskSafe::sendPostTask(void *pvParameters) {
    TaskParams* params = (TaskParams*)pvParameters;
    HTTPClientTaskSafe* httpClientTaskSafe = params->httpClientTaskSafe;
    String transactionUUID = params->transactionUUID;
    String url = params->url;
    String message = params->message;

    if (xSemaphoreTake(httpClientTaskSafe->httpMutex, portMAX_DELAY)) {
        HTTPClient http;
        http.begin(url);
        httpClientTaskSafe->logUtility.loglnInfoTransactionID(transactionUUID, "Sending POST request. URL: " + url + ", Message: " + message);

        int httpResponseCode = http.POST(message);
        if (httpResponseCode == 200 || httpResponseCode == 201) {
            httpClientTaskSafe->logUtility.loglnInfoTransactionID(transactionUUID, "POST request successful: " + String(httpResponseCode) + " " + http.getString());
        } else {
            httpClientTaskSafe->logUtility.loglnInfoTransactionID(transactionUUID, "POST request failed: " + String(httpResponseCode) + " " + http.getString());
        }
        http.end();
        xSemaphoreGive(httpClientTaskSafe->httpMutex);
    }

    // delete the task once done
    vTaskDelete(NULL);
}
