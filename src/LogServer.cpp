#include "LogServer.h"

LogServer::LogServer(LogUtility& logUtility)
    : logUtility(logUtility), server(80) {}

void LogServer::setup() {
    // Define the web server routes
    server.on("/", [this]() {
        String response = "<style>"
                        ".log-entry, .pretty-json { "
                        "    font-family: Arial, sans-serif; "
                        "    font-size: 14px; "
                        "    margin: 5px; "
                        "    padding: 10px; "
                        "    border: 1px solid #ccc; "
                        "    border-radius: 5px; "
                        "    cursor: pointer; "
                        "} "
                        ".pretty-json { "
                        "    white-space: pre-wrap; "
                        "    background-color: #FFFFFF; "
                        "} "
                        "</style>"
                        "<script>"
                        "function togglePretty(element) {"
                        "   let originalText = element.getAttribute('data-original');"
                        "   let currentText = element.innerHTML;"
                        "   if (currentText === originalText) {"
                        "       try {"
                        "           let json = JSON.parse(originalText);"
                        "           let prettyJson = JSON.stringify(json, null, 2);"
                        "           element.innerHTML = '<pre class=\"pretty-json\">' + prettyJson + '</pre>';"
                        "       } catch (e) {"
                        "           console.error('Failed to parse JSON:', e);"
                        "       }"
                        "   } else {"
                        "       element.innerHTML = originalText;"
                        "   }"
                        "}"
                        "</script>"
                        "<h1>StormerESP32 Logs</h1><div id=\"logs\">" + logUtility.getLogsHTML() + "</div>";
        server.send(200, "text/html", response);
    });

    server.begin(); // Start the server
}

void LogServer::handle() {
    server.handleClient(); // Handle incoming clients if the server is enabled
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
