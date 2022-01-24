//
// Created by janik on 24.01.2022.
//

#include "Board.h"

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
