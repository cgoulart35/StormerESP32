#ifndef LOG_UTILITY_H
#define LOG_UTILITY_H

#include <deque>
#include <WebServer.h>

class LogUtility {
private:
    WebServer server;
    bool logTimestamp;
    std::deque<String> logDeque;

public:
    LogUtility();
    void setup();
    void startLogServer();
    void handle(); // To be called in loop()
    void logln(const String& message);
    void log(const String& message);
    String getCurrentTime();
    String getLogs();
};

#endif // LOG_UTILITY_H
