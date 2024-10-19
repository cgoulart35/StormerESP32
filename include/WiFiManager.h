#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

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
    boolean ledConfigured;
    boolean rgbSwitch;
    boolean offineMode;

    void setupLedPins();
    void setRgbColor(boolean r, boolean g, boolean b);
};

#endif
