//
// Created by janik on 24.01.2022.
//

#include "../.pio/libdeps/uno/FastLED/src/FastLED.h"

#ifndef UNTITLED1_BOARD_H
#define UNTITLED1_BOARD_H


class Board {
public:
    static const int NUM_LEDS = 148;
    void init();
    CRGB *getLeds();
    void clearAllLeds();
    void setBrightness(int brightness);
    void show();

    void turnOnLightsForMinutes(int minutes);
    void turnOnLightsForHour(int hour);

    void turnOnLightsForRest(int i);

    void turnOnDefaultLights();

private:
    CRGB leds[NUM_LEDS];
    void turnOnLeds(const int* indexes, int arraySize);
};


#endif //UNTITLED1_BOARD_H
