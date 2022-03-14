#include <Arduino.h>
#include "../.pio/libdeps/uno/RTClib/src/RTClib.h"
#include <Wire.h>
#include "Board.h"


RTC_DS1307 rtc;
auto board = new Board;
DateTime dateTime;

int minBrightness = 20;
int maxBrightness = 100;

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

int hour = 1;
int minute = 0;

void loop() {
    minute++;
    //    X:25 => "füf vor haubi X+1"
    int minuteRounded = roundDownToFive(minute);
    int rest = minute - minuteRounded;
    if (minute == 25) {
        hour++;
    }
    if (minute == 60) {
        minute = 0;
    }
    if (hour == 13) {
        hour = 1;
    }
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minuteRounded);
    Serial.print(" rest:");
    Serial.print(rest);
    Serial.print("\n");

    board->clearAllLeds();
    board->turnOnDefaultLights();
    board->turnOnLightsForHour(hour);
    board->turnOnLightsForMinutes(minuteRounded);
    board->turnOnLightsForRest(rest);

    calculateAndSetBrightness();

    board->show();

    delay(200);

//    DateTime now = rtc.now();
//    for (int i = 0; i < NUM_LEDS; ++i) {
//        leds[i] = LED_COLOR;
//        FastLED.show();
//        delay(100);
//        leds[i] = CRGB::Black;
//    }
}

int roundDownToFive(int number) {
    return (number/5) * 5;
}

void calculateAndSetBrightness() {
    float analogValue = analogRead(A0);
    float percentage = analogValue / 1024;
    float brightness = minBrightness + (maxBrightness - minBrightness) * percentage;
    board->setBrightness((int) brightness);
}