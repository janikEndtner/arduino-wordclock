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

void Board::turnOnLightsForHour(int hour) {
    switch (hour) {
        case 1: {
            int indexes[3] = {60, 61, 62};
            this->turnOnLeds(indexes, 3);
            break;
        }
        case 2: {
            int indexes[4] = {99, 100, 101, 102};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 3: {
            int indexes[4] = {116, 117, 118, 119};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 4: {
            int indexes[5] = {89, 90, 91, 92, 93};
            this->turnOnLeds(indexes, 5);
            break;
        }
        case 5: {
            int indexes[4] = {132, 133, 134, 135};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 6: {
            int indexes[6] = {62, 63, 64, 65, 66, 67};
            this->turnOnLeds(indexes, 6);
            break;
        }
        case 7: {
            int indexes[5] = {66, 67, 68, 69, 70};
            this->turnOnLeds(indexes, 5);
            break;
        }
        case 8: {
            int indexes[5] = {84, 85, 86, 87, 88};
            this->turnOnLeds(indexes, 5);
            break;
        }
        case 9: {
            int indexes[4] = {137, 138, 139, 140};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 10: {
            int indexes[4] = {108, 109, 110, 111};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 11: {
            int indexes[4] = {128, 129, 130, 131};
            this->turnOnLeds(indexes, 4);
            break;
        }
        case 12: {
            int indexes[6] = {78, 79, 80, 81, 82, 83};
            this->turnOnLeds(indexes, 6);
            break;
        }
    }
}

void Board::turnOnLightsForMinutes(int minutes) {
    int vor[3] = {44, 45, 46};
    int ab[2] = {37, 38};

    int fuef[3] = {9, 10, 11};
    int zaeh[3] = {18, 19, 20};
    int viertu[6] = {12, 13, 14, 15, 16, 17};
    int zwaenzg[6] = {25, 26, 27, 28, 29, 30};
    int haubi[5] = {51, 52, 53, 54, 55};

    switch (minutes) {
        case 0: {
            // no light
            break;
        }
        case 5: {
            turnOnLeds(fuef, 3);
            turnOnLeds(ab, 2);
            break;
        }
        case 10: {
            turnOnLeds(zaeh, 3);
            turnOnLeds(ab, 2);
            break;
        }
        case 15: {
            turnOnLeds(viertu, 6);
            turnOnLeds(ab, 2);
            break;
        }
        case 20: {
            turnOnLeds(zwaenzg, 6);
            turnOnLeds(ab, 2);
            break;
        }
        case 25: {
            turnOnLeds(fuef, 3);
            turnOnLeds(vor, 3);
            turnOnLeds(haubi, 5);
            break;
        }
        case 30: {
            turnOnLeds(haubi, 5);
            break;
        }
        case 35: {
            turnOnLeds(fuef, 3);
            turnOnLeds(ab, 2);
            turnOnLeds(haubi, 5);
            break;
        }
        case 40: {
            turnOnLeds(zwaenzg, 6);
            turnOnLeds(vor, 3);
            break;
        }
        case 45: {
            turnOnLeds(viertu, 6);
            turnOnLeds(vor, 3);
            break;
        }
        case 50: {
            turnOnLeds(zaeh, 3);
            turnOnLeds(vor, 3);
            break;
        }
        case 55: {
            turnOnLeds(fuef, 3);
            turnOnLeds(vor, 3);
            break;
        }
        default: {
            Serial.print("undefined minute: ");
            Serial.print(minutes);
            Serial.print("\n");
        }
    }
}

void Board::turnOnLeds(const int* indexes, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        this->leds[indexes[i]] = CRGB::White;
    }
}

void Board::turnOnLightsForRest(int i) {
    if (i >= 1) {
        Serial.print(i);
        leds[144] = CRGB::White;
    }
    if (i >= 2) {
        leds[145] = CRGB::White;
    }
    if (i >= 3) {
        leds[146] = CRGB::White;
    }
    if (i == 4) {
        leds[147] = CRGB::White;
    }
}

void Board::turnOnDefaultLights() {
    // turns on lights for "es isch"
    int indexes[6] = {1, 2, 4, 5, 6, 7};
    this->turnOnLeds(indexes, 6);
}
