#include "WiFiManager.h"

WiFiManager::WiFiManager(LogUtility& logUtility)
    : logUtility(logUtility), previousMillis(0), isDisconnected(true),
    ledConfigured(false), rgbSwitch(false), offineMode(true) {}

void WiFiManager::connect() {
    if (!ledConfigured) {
        setupLedPins();
        setRgbColor(1, 0, 0);
        ledConfigured = true;
    }

    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    logUtility.loglnInfo("Connecting to Wi-Fi...");
}

void WiFiManager::handle() {
    unsigned long currentMillis = millis();

    // If disconnected flash the RGB LED
    if (WiFi.status() !=WL_CONNECTED) {
        if(rgbSwitch) {
            setRgbColor(0, 0, 0);
            rgbSwitch = false;
        } else {
            if (offineMode) {
                setRgbColor(1, 0, 0);
            } else {
                setRgbColor(0, 0, 1);
            }
            rgbSwitch = true;
        }
        
    }

    // Check Wi-Fi connection and reconnect if necessary
    if (WiFi.status() != WL_CONNECTED && (currentMillis - previousMillis >= WIFI_RECONNECT_INTERVAL)) {
        logUtility.loglnInfo("Wi-Fi disconnected. Attempting reconnection...");

        // Try to reconnect to Wi-Fi
        isDisconnected = true;
        previousMillis = currentMillis;
        connect(); 

    // If reconection failed, but connected before next reattempt
    } else if (isDisconnected && WiFi.status() == WL_CONNECTED) {
        logUtility.loglnInfo("Wi-Fi connected! IP address: " + WiFi.localIP().toString());
        isDisconnected = false;
        setRgbColor(0, 1, 0);
        
        if (offineMode) {
            configTzTime(TIMEZONE, "pool.ntp.org", "time.nist.gov"); // Automatically adjusts for DST
            offineMode = false;
        }
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void WiFiManager::setupLedPins() {
  // Set the RGB LED pins as output
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void WiFiManager::setRgbColor(boolean r, boolean g, boolean b) {
  // Set the LED color based on r, g, b values (0 or 1)
  digitalWrite(LED_RED, r ? LOW : HIGH);   // Red channel (LOW to turn on)
  digitalWrite(LED_GREEN, g ? LOW : HIGH); // Green channel
  digitalWrite(LED_BLUE, b ? LOW : HIGH);  // Blue channel
}
