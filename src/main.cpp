#include <Arduino.h>
#include "../.pio/libdeps/uno/RTClib/src/RTClib.h"
#include <Wire.h>
#include "Board.h"


RTC_DS1307 rtc;
auto board = new Board;

int minBrightness = 20;
int maxBrightness = 100;
// we get max 1024 from input. set this value to reach 100% brightness earlier
int brightestAtXBit = 800;

int roundDownToFive(int number);
void calculateAndSetBrightness();

void setup() {
    delay(3000); // power-up safety delay
    board->init();

    Serial.begin(9600);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
    }
    if (!rtc.isrunning()) {
        Serial.println("RTC is NOT running!");
    }
    if (rtc.isrunning()){
        Serial.println("RTC is running. Setting initial time...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void loop() {

    DateTime now = rtc.now();
    int hour = now.hour();
    int minute = now.minute();
    Serial.println(now.timestamp());

    int minuteRounded = roundDownToFive(minute);
    int rest = minute - minuteRounded;
    if (minute >= 25) {
        hour++;
    }

    board->clearAllLeds();
    board->turnOnDefaultLights();
    board->turnOnLightsForHour(hour);
    board->turnOnLightsForMinutes(minuteRounded);
    board->turnOnLightsForRest(rest);

    calculateAndSetBrightness();

    board->show();

    delay(1000);
}

int roundDownToFive(int number) {
    return (number/5) * 5;
}

void calculateAndSetBrightness() {
    float analogValue = analogRead(A0);
    float percentage = analogValue / brightestAtXBit;
    float brightness = minBrightness + (maxBrightness - minBrightness) * percentage;
    brightness = min(100, brightness);
    Serial.print("Brightness: ");
    Serial.println(brightness);
    board->setBrightness((int) brightness);
}