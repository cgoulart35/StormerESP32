#include "LogUtility.h"
#include <time.h>

LogUtility::LogUtility()
    : head(0), logCount(0), server(80), serverStarted(false), logTimestamp(true) {
}

void LogUtility::startLogServer() {
    if (!serverStarted) {
        // Get time frim internet
        configTime(0, 0, "pool.ntp.org", "time.nist.gov");

        // Define the web server routes
        server.on("/", [this]() {
            server.send(200, "text/html", "<h1>ESP32 Logs</h1><pre>" + getLogs() + "</pre>");
        });

        server.begin(); // Start the server
        serverStarted = true; // Mark the server as started
    }
}

void LogUtility::handle() {
    if (serverStarted) {
        server.handleClient(); // Handle incoming clients if the server has started
    }
}

void LogUtility::logln(const String& message) {
    String finalMessage = getCurrentTime() + message;
    logs[head] = finalMessage + "\n";

    head = (head + 1) % MAX_LOG_ENTRIES;
    if (logCount < MAX_LOG_ENTRIES) {
        logCount++; // Increase log count until max is reached
    }

    Serial.println(finalMessage);
    logTimestamp = true;
}

void LogUtility::log(const String& message) {
    String finalMessage = getCurrentTime() + message;
    logs[head] = finalMessage;
    
    head = (head + 1) % MAX_LOG_ENTRIES;
    if (logCount < MAX_LOG_ENTRIES) {
        logCount++; // Increase log count until max is reached
    }

    Serial.print(finalMessage);
    logTimestamp = false;
}

String LogUtility::getCurrentTime() {
    if (!logTimestamp) {
        return "";
    }
    
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "N/A"; // Return if time cannot be obtained
    }
    
    // Format the time as HH:MM:SS
    char timeString[20];
    strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeinfo);
    
    return String(timeString) + "   "; // Return formatted time as String
}

String LogUtility::getLogs() {
    String allLogs = "";
    for (int i = 0; i < logCount; i++) {
        // Calculate the index in the circular buffer
        int index = (head - logCount + i + MAX_LOG_ENTRIES) % MAX_LOG_ENTRIES;
        allLogs += logs[index];
    }
    return allLogs; // Return all logs as a single string
}
