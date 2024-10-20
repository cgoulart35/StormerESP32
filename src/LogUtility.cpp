#include "LogUtility.h"

LogUtility::LogUtility() {
    uuid.setVariant4Mode();
    logMutex = xSemaphoreCreateMutex();
}

void LogUtility::loglnInfo(const String& message) {
    logln("INFO", "", message);
}

void LogUtility::loglnError(const String& message) {
    logln("ERROR", "", message);
}

void LogUtility::loglnInfoTransactionID(const String& transactionUUID, const String& message) {
    logln("INFO", transactionUUID, message);
}

void LogUtility::loglnErrorTransactionID(const String& transactionUUID, const String& message) {
    logln("ERROR", transactionUUID, message);
}

String LogUtility::getLogsHTML() {
    String allLogs;
    if (xSemaphoreTake(logMutex, portMAX_DELAY)) {
        // Estimate total size of all logs
        size_t totalSize = 0;
        for (int i = logDeque.size() - 1; i >= 0; i--) {
            totalSize += logDeque[i].length();
        }

        // Reserve the necessary space in one go
        allLogs.reserve(totalSize); // Preallocate memory

        // Append all log entries in the deque
        for (int i = logDeque.size() - 1; i >= 0; i--) {
            allLogs += "<div class='log-entry' data-original='" + logDeque[i] + "' onclick='togglePretty(this)'>" + logDeque[i] + "</div>";
        }
        xSemaphoreGive(logMutex);
    }

    return allLogs;
}

String LogUtility::getCurrentTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "N/A"; // Return if time cannot be obtained
    }

    // Format the time as HH:MM:SS
    char timeString[20];
    strftime(timeString, sizeof(timeString), "%I:%M:%S %p %Z", &timeinfo);
    
    return String(timeString); // Return formatted time as String
}

String LogUtility::generateTransactionUUID() {
    uuid.generate();
    return uuid.toCharArray();
}

void LogUtility::logln(const String& level, const String& transactionUUID, const String& message) {
    JsonDocument doc;
    doc["time"] = getCurrentTime();
    doc["level"] = level;
    if (transactionUUID != "") {
        doc["transactionUUID"] = transactionUUID;
    }
    doc["message"] = message;

    String jsonString;
    serializeJson(doc, jsonString);

    addLogToStack(jsonString);
    Serial.println(jsonString);
}

void LogUtility::addLogToStack(const String& message) {
    if (xSemaphoreTake(logMutex, portMAX_DELAY)) {
        logDeque.push_front(message);
        if (logDeque.size() > MAX_LOG_ENTRIES) {
            logDeque.pop_back();
        }
        xSemaphoreGive(logMutex);
    }
}
