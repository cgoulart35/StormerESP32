#ifndef LOG_UTILITY_H
#define LOG_UTILITY_H

#include <ArduinoJson.h>
#include <WebServer.h>
#include <deque>
#include <UUID.h>

class LogUtility {
public:
    LogUtility();
    void loglnInfo(const String& message);
    void loglnError(const String& message);
    void loglnInfoTransactionID(const String& transactionUUID, const String& message);
    void loglnErrorTransactionID(const String& transactionUUID, const String& message);
    String getLogsHTML();
    String getCurrentTime();
    String generateTransactionUUID();

private:
    UUID uuid;
    std::deque<String> logDeque;
    SemaphoreHandle_t logMutex;

    void logln(const String& level, const String& transactionUUID, const String& message);
    void addLogToStack(const String& message);
};

#endif
