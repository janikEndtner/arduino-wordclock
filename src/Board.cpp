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

void Board::turnOnLightsForHour(uint8_t hour) {
    switch (hour) {
        case 1: {
            int indexes[3] = {61, 62, 63};
            this->turnOnLeds(indexes, 3);
            break;
        }
        case 2: {
            int indexes[4] = {100, 101, 102, 103};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 3: {
            int indexes[4] = {117, 118, 119, 120};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 4: {
            int indexes[4] = {90, 91, 92, 93};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 5: {
            int indexes[4] = {133, 134, 135, 136};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 6: {
            int indexes[4] = {63, 64, 65, 66};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 7: {
            int indexes[5] = {67, 68, 69, 70, 71};
            this->turnOnLeds(indexes, 5);
            break;
        }
        case 8: {
            int indexes[5] = {85, 86, 87, 88, 89};
            this->turnOnLeds(indexes, 5);
            break;
        }
        case 9: {
            int indexes[4] = {138, 139, 140, 141};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 10: {
            int indexes[4] = {109, 110, 111, 112};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 11: {
            int indexes[4] = {117, 118, 119, 120};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 12: {
            int indexes[6] = {79, 80, 81, 82, 83, 84};
            this->turnOnLeds(indexes, 6);
            break;
        }
    }
}

void Board::turnOnLightsForMinute(uint8_t i) {
    leds[2] = CRGB::White;
    leds[5] = CRGB::White;
    leds[7] = CRGB::White;
}

void Board::turnOnLeds(const int* indexes, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        this->leds[indexes[i]] = CRGB::White;
    }
}
