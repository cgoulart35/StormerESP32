#ifndef LOG_UTILITY_H
#define LOG_UTILITY_H

#include <WebServer.h>
#include <time.h>
#include <deque>

class LogUtility {
public:
    LogUtility();
    void setup();
    void handle(); // To be called in loop()
    void loglnInfo(const String& message);
    void logInfo(const String& message);
    void loglnError(const String& message);
    void logError(const String& message);
    String getLogs();

private:
    WebServer server;
    bool logTimestampOnNext;
    std::deque<String> logDeque;

    void startLogServer();
    void logln(const String& level, const String& message);
    void log(const String& level, const String& message);
    void addLogToStack(const String& message);
    String getLevel(const String& level);
    String getCurrentTime();
};

#endif // LOG_UTILITY_H
