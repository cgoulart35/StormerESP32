#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <LogUtility.h>

class WiFiManager {
public:
    WiFiManager(LogUtility& logUtility, const char* ssid, const char* password);
    void connect();
    void handle();
    
private:
    LogUtility& logUtility;
    const char* ssid;
    const char* password;
};

#endif
