//
// Created by janik on 24.01.2022.
//

#include "Board.h"

#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

void Board::init() {
    const int letPin = 5;
    FastLED.addLeds<LED_TYPE, letPin, COLOR_ORDER>(this->getLeds(), Board::NUM_LEDS).setCorrection(TypicalLEDStrip);
}

void Board::setFirstLed() {
    leds[2] = CRGB::White;
    leds[5] = CRGB::White;
    leds[7] = CRGB::White;
}

CRGB *Board::getLeds() {
    return leds;
}

void Board::clearAllLeds() {
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = CRGB::Black;
    }
}

void Board::setBrightness(int brightness) {
    FastLED.setBrightness(brightness);
}

void Board::show() {
    FastLED.show();
}
