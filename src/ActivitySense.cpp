#include "ActivitySense.h"

#define TRIG_PIN   0
#define ECHO_PIN   1
#define BUZZER_PIN 2

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

ActivitySense::ActivitySense(LogUtility& logUtility)
    : logUtility(logUtility), notifyRun(logUtility, NOTIFY_RUN_CHANNEL_ACTIVITY_SENSE) {
        duration = 0;
        distance = 0.0;
    }

void ActivitySense::setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void ActivitySense::handle() {
    // clears the trigPin
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    // measure duration of pulse from ECHO pin
    duration = pulseIn(ECHO_PIN, HIGH);

    // if the pulse duration is valid, calculate the distance
    if (duration > 0) {
        // calculate the distance in cm
        distance = duration * SOUND_SPEED/2;
        // convert to inches
        distance = distance * CM_TO_INCH;
    } else {
        // if no echo received, set distance to a high value to avoid triggering the buzzer
        distance = DISTANCE_THRESHOLD_INCHES + 1;
    }

    simpleBuzzerToggle();
    //complexBuzzerSong();

    vTaskDelay(100 / portTICK_PERIOD_MS);
}

void ActivitySense::simpleBuzzerToggle() {
    // turn on buzzer
    if (distance < DISTANCE_THRESHOLD_INCHES) {
        if (!buzzerState) {
            String time = logUtility.getCurrentTime();
            logUtility.loglnInfo("Buzzer activated: Distance below threshold of " + String(DISTANCE_THRESHOLD_INCHES) + " inches - " + distance);
            notifyRun.publish("Buzzer activated at " + time);
        }
        digitalWrite(BUZZER_PIN, HIGH);
        buzzerState = true;
    // turn off buzzer
    } else {
        if (buzzerState) {
            logUtility.loglnInfo("Buzzer deactivated: Distance above threshold of " + String(DISTANCE_THRESHOLD_INCHES) + " inches - " + distance);
        }
        digitalWrite(BUZZER_PIN, LOW);
        buzzerState = false;
    }
}

void ActivitySense::complexBuzzerSong() {

}
