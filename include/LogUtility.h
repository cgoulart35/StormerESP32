#ifndef LOG_UTILITY_H
#define LOG_UTILITY_H

#include <WebServer.h>

class LogUtility {
private:
    WebServer server;
    bool serverStarted;
    bool logTimestamp;

    static const int MAX_LOG_ENTRIES = 300; // Maximum number of log entries
    String logs[MAX_LOG_ENTRIES]; // Circular buffer for log messages
    int head; // Index for the next log entry
    int logCount; // Current count of log entries

public:
    LogUtility();
    void startLogServer();
    void handle(); // To be called in loop()
    void logln(const String& message);
    void log(const String& message);
    String getCurrentTime();
    String getLogs();
};

#endif // LOG_UTILITY_H
