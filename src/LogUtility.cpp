#include "LogUtility.h"
#include <time.h>

LogUtility::LogUtility()
    : server(80), logTimestampOnNext(true) {
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

void LogUtility::loglnInfo(const String& message) {
    logln("[INFO]   ", message);
}

void LogUtility::logInfo(const String& message) {
    log("[INFO]   ", message);
}

void LogUtility::loglnError(const String& message) {
    logln("[ERROR]   ", message);
}

void LogUtility::logError(const String& message) {
    log("[ERROR]   ", message);
}

void LogUtility::logln(const String& level, const String& message) {
    String potentialTimestampMsg = getCurrentTime() + getLevel(level) + message;
    String finalMessage = potentialTimestampMsg + "\n";

    addLogToStack(finalMessage);
    Serial.println(potentialTimestampMsg);
    logTimestampOnNext = true;
}

void LogUtility::log(const String& level, const String& message) {
    String potentialTimestampMsg = getCurrentTime() + getLevel(level) + message;

    addLogToStack(potentialTimestampMsg);
    Serial.print(potentialTimestampMsg);
    logTimestampOnNext = false;
}

void LogUtility::addLogToStack(const String& message) {
    if (logTimestampOnNext) {
        logDeque.push_front(message);
        if (logDeque.size() > MAX_LOG_ENTRIES) {
            logDeque.pop_back();
        }
    } else {
        String newLog = logDeque.front() += message;
        logDeque.pop_front();
        logDeque.push_front(newLog);
    }
}

String LogUtility::getLevel(const String& level) {
    if (!logTimestampOnNext) {
        return "";
    } else {
        return level;
    }
}

String LogUtility::getCurrentTime() {
    if (!logTimestampOnNext) {
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
    // Estimate total size of all logs
    size_t totalSize = 0;
    for (int i = logDeque.size() - 1; i >= 0; i--) {
        totalSize += logDeque[i].length();
    }

    // Reserve the necessary space in one go
    String allLogs;
    allLogs.reserve(totalSize); // Preallocate memory

    // Append all log entries in the deque
    for (int i = logDeque.size() - 1; i >= 0; i--) {
        allLogs += logDeque[i];
    }

    return allLogs;
}

