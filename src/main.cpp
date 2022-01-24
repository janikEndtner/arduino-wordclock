#include <Arduino.h>
#include "../.pio/libdeps/uno/RTClib/src/RTClib.h"
#include <Wire.h>
#include "Board.h"


RTC_DS1307 rtc;

void setup() {
    delay(3000); // power-up safety delay
    auto board = new Board;
    board->setBrightness(20);
    board->init();
    board->clearAllLeds();
    board->setFirstLed();
    board->show();

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
//    for (int i = 0; i < NUM_LEDS; ++i) {
//        leds[i] = LED_COLOR;
//        FastLED.show();
//        delay(100);
//        leds[i] = CRGB::Black;
//    }
}