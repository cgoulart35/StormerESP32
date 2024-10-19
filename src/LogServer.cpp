#include "LogServer.h"

LogServer::LogServer(LogUtility& logUtility)
    : logUtility(logUtility), server(80) {}

void LogServer::setup() {
    if (ENABLE_LOG_SERVER) {
        startLogServer();
    }
}

void LogServer::startLogServer() {
    // Define the web server routes
    server.on("/", [this]() {
        server.send(200, "text/html", "<h1>StormerESP32 Logs</h1><pre>" + logUtility.getLogs() + "</pre>");
    });

    server.begin(); // Start the server
}

void LogServer::handle() {
    if (ENABLE_LOG_SERVER) {
        server.handleClient(); // Handle incoming clients if the server is enabled
    }
}
