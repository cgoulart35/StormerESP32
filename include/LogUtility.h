#ifndef LOG_UTILITY_H
#define LOG_UTILITY_H

#include <WebServer.h>
#include <deque>

class LogUtility {
public:
    LogUtility();
    void loglnInfo(const String& message);
    void loglnError(const String& message);
    String getLogs();
    String getCurrentTime();

private:
    std::deque<String> logDeque;
    SemaphoreHandle_t logMutex;

    void logln(const String& level, const String& message);
    void addLogToStack(const String& message);
};

#endif
