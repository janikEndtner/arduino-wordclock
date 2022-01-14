#include <Arduino.h>
#include "../.pio/libdeps/uno/RTClib/src/RTClib.h"
#include "../.pio/libdeps/uno/FastLED/src/FastLED.h"
#include <Wire.h>

RTC_DS1307 rtc;

#define LED_PIN     5
#define NUM_LEDS    144
#define BRIGHTNESS  20
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define LED_COLOR CRGB::White

CRGB leds[NUM_LEDS];

void setup() {
    delay(3000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
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
    //Word *word = new Word;
    DateTime now = rtc.now();
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = LED_COLOR;
        FastLED.show();
        delay(100);
        leds[i] = CRGB::Black;
    }
}