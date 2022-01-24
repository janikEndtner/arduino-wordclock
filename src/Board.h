//
// Created by janik on 24.01.2022.
//

#include "../.pio/libdeps/uno/FastLED/src/FastLED.h"

#ifndef UNTITLED1_BOARD_H
#define UNTITLED1_BOARD_H


class Board {
public:
    static const int NUM_LEDS = 144;
    CRGB *getLeds();
    void setFirstLed();
    void clearAllLeds();

private:
    CRGB leds[NUM_LEDS];
};


#endif //UNTITLED1_BOARD_H
