#include "NotifyRun.h"

NotifyRun::NotifyRun(LogUtility& logUtility, const String& channelId)
    : logUtility(logUtility), channelId(channelId) {}

int NotifyRun::publish(const String& message) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "https://notify.run/" + channelId;
        http.begin(url);
        logUtility.loglnInfo("Publishing message to channel " + channelId + ": " + message);

        int httpResponseCode = http.POST(message);
        if (httpResponseCode == 200 || httpResponseCode == 201) {
            logUtility.loglnInfo("Published successfully: " + String(httpResponseCode) + " " + http.getString());
        } else {
            logUtility.loglnInfo("Failed to publish: " + String(httpResponseCode) + " " + http.getString());
        }
        http.end();
        return httpResponseCode;
    }
}
