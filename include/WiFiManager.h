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
    boolean ledConfigured;
    boolean rgbSwitch;
    boolean offineMode;

    void setupLedPins();
    void toggleLED();
    void setRgbColor(boolean r, boolean g, boolean b);
};

#endif
