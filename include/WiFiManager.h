#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <LogUtility.h>

class WiFiManager {
public:
    WiFiManager(LogUtility& logUtility);
    void connect();
    void handle();
    
private:
    LogUtility& logUtility;
    unsigned long previousMillis;
    boolean isDisconnected;
};

#endif
