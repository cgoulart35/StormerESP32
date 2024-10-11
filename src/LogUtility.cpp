#include "LogUtility.h"
#include <time.h>

LogUtility::LogUtility()
    : server(80), logTimestamp(true) {
}

void LogUtility::setup() {
    // Get time frim internet
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    if (ENABLE_LOG_SERVER) {
        startLogServer();
    }
}

void LogUtility::startLogServer() {
    // Define the web server routes
    server.on("/", [this]() {
        server.send(200, "text/html", "<h1>StormerESP32 Logs</h1><pre>" + getLogs() + "</pre>");
    });

    server.begin(); // Start the server
}

void LogUtility::handle() {
    if (ENABLE_LOG_SERVER) {
        server.handleClient(); // Handle incoming clients if the server is enabled
    }
}

void LogUtility::logln(const String& message) {
    String timestampedMessage = getCurrentTime() + message;
    String finalMessage = timestampedMessage + "logDeque.size(): " + logDeque.size() + "\n";

    logDeque.push_front(finalMessage);
    if (logDeque.size() > MAX_LOG_ENTRIES) {
        logDeque.pop_back();
    }

    Serial.println(timestampedMessage);
    logTimestamp = true;
}

void LogUtility::log(const String& message) {
    String timestampedMessage = getCurrentTime() + message;
    String finalMessage = timestampedMessage;

    if (logDeque.empty()) {
        logDeque.push_front(finalMessage);
    } else {
        String newLog = logDeque.front() += finalMessage;
        logDeque.pop_front();
        logDeque.push_front(newLog);
    }

    Serial.print(timestampedMessage);
    logTimestamp = false;
}

String LogUtility::getCurrentTime() {
    if (!logTimestamp) {
        return "";
    }
    
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "N/A   "; // Return if time cannot be obtained
    }
    
    // Format the time as HH:MM:SS
    char timeString[20];
    strftime(timeString, sizeof(timeString), "%H:%M:%S", &timeinfo);
    
    return String(timeString) + "   "; // Return formatted time as String
}

String LogUtility::getLogs() {
    String allLogs = "";
    for (int i = logDeque.size() - 1; i >= 0; i--) {
        allLogs += logDeque[i];
    }
    return allLogs; // Return all logs as a single string
}
