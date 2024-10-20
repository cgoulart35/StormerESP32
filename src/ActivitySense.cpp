#include "ActivitySense.h"

#define TRIG_PIN   0
#define ECHO_PIN   1
#define BUZZER_PIN 2

ActivitySense::ActivitySense(LogUtility& logUtility)
    : logUtility(logUtility), notifyRun(logUtility, NOTIFY_RUN_CHANNEL_ACTIVITY_SENSE) {
        duration_us = 0;
        distance_in = 0.0;
    }

void ActivitySense::setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void ActivitySense::handle() {
    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // measure duration of pulse from ECHO pin
    duration_us = pulseIn(ECHO_PIN, HIGH);

    // check if the pulse duration is valid
    if (duration_us > 0) {
        // calculate the distance in centimeters and convert to inches
        distance_in = (0.017 * duration_us) / 2.54;        
    } else {
        // If no echo received, set distance to a high value to avoid triggering the buzzer
        distance_in = DISTANCE_THRESHOLD_INCHES + 1;
    }

    simpleBuzzerToggle();
    //complexBuzzerSong();
}

void ActivitySense::simpleBuzzerToggle() {
    // turn on buzzer
    if (distance_in < DISTANCE_THRESHOLD_INCHES) {
        if (!buzzerState) {
            String time = logUtility.getCurrentTime();
            logUtility.loglnInfo("Buzzer activated: Distance below threshold of " + String(DISTANCE_THRESHOLD_INCHES) + " inches - " + distance_in);
            notifyRun.publish("Buzzer activated at " + time);
        }
        digitalWrite(BUZZER_PIN, HIGH);
        buzzerState = true;
    // turn off buzzer
    } else {
        if (buzzerState) {
            logUtility.loglnInfo("Buzzer deactivated: Distance above threshold of " + String(DISTANCE_THRESHOLD_INCHES) + " inches - " + distance_in);
        }
        digitalWrite(BUZZER_PIN, LOW);
        buzzerState = false;
    }
}

void ActivitySense::complexBuzzerSong() {

}
