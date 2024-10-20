#include "LogServer.h"

LogServer::LogServer(LogUtility& logUtility)
    : logUtility(logUtility), server(80) {}

void LogServer::setup() {
    // Define the web server routes
    server.on("/", [this]() {
        server.send(200, "text/html", "<h1>StormerESP32 Logs</h1><pre>" + logUtility.getLogs() + "</pre>");
    });

    server.begin(); // Start the server
}

void LogServer::handle() {
    server.handleClient(); // Handle incoming clients if the server is enabled
}
