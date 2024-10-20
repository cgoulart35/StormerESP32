#ifndef LOG_SERVER_H
#define LOG_SERVER_H

#include <WebServer.h>
#include <LogUtility.h>

class LogServer {
public:
    LogServer(LogUtility& logUtility);
    void setup();
    void handle(); // To be called in loop()

private:
    LogUtility& logUtility;
    WebServer server;
};

#endif
