#include <Arduino.h>
#include "../.pio/libdeps/uno/RTClib/src/RTClib.h"
#include <Wire.h>
#include "Board.h"


RTC_DS1307 rtc;
auto board = new Board;

int minBrightness = 20;
int maxBrightness = 100;
// we get max 1024 from input. set this value to reach 100% brightness earlier
int brightestAtXBit = 1024;

int previousBrightness;
int brightnessChanges = 0;
bool summerTime = false;

DateTime birthdays[2] = {
        DateTime(1989, 01, 13, 0, 0, 0),
        DateTime(1993, 05, 17, 0, 0, 0)
};

int roundDownToFive(int number);
int calculateBrightness();
void calculateSummerTime(int second, int brightness);
bool isHappyBirthday(DateTime* now);

void setup() {
    delay(3000); // power-up safety delay
    board->init();

    Serial.begin(9600);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
    }
    if (!rtc.isrunning()) {
        Serial.println("RTC is NOT running! Setting initial time...");
        rtc.adjust(DateTime(2022, 6, 26, 16, 48, 0));
    }
    if (rtc.isrunning()){
        Serial.println("RTC is running.");
    }
}

void loop() {

    DateTime now = rtc.now();
    int hour = now.hour();

    if (summerTime) {
        hour++;
    }

    int minute = now.minute();
    Serial.println(now.timestamp());

    int minuteRounded = roundDownToFive(minute);
    int rest = minute - minuteRounded;
    if (minute >= 25) {
        hour++;
    }

    board->clearAllLeds();
    if (isHappyBirthday(&now)) {
        board->turnOnHappyBirthdayLeds();
    } else {
        board->turnOnDefaultLights();
        board->turnOnLightsForHour(hour);
        board->turnOnLightsForMinutes(minuteRounded);
        board->turnOnLightsForRest(rest);
    }

    int brightness = calculateBrightness();
    board->setBrightness(brightness);
    calculateSummerTime(now.second(), brightness);
    previousBrightness = brightness;

    board->show();

    delay(1000);
}

int roundDownToFive(int number) {
    return (number/5) * 5;
}

int calculateBrightness() {
    float analogValue = analogRead(A0);
    float percentage = analogValue / brightestAtXBit;
    float brightness = minBrightness + (maxBrightness - minBrightness) * percentage;
    brightness = min(100, brightness);
    Serial.print("Brightness: ");
    Serial.println(brightness);
    return (int) brightness;
}

/**
 * ??ber das Abdecken des Helligkeitssensors soll es m??glich sein, die Sommerzeit zu setzen
 * oder wieder zu Winterzeit zu wechseln. Daf??r muss der Sensor dreimal in kurzer Zeit
 * verdunkelt und wieder erhellt werden.
 */
void calculateSummerTime(int second, int brightness) {
    // alle dreissig sekunden reduzieren wir die Anzahl Wechsel
    if (second % 30 == 0 && brightnessChanges > 0) {
        brightnessChanges--;
    }
    // Wenn sich die Helligkeit um mindesten 20% ver??ndert, werten wir dies als
    // grosse Ver??nderung
    float brightnessChange = abs((brightness - previousBrightness) / previousBrightness);
    Serial.println(brightnessChanges);
    if (brightnessChange > 0.2) {
        brightnessChanges++;
    }
    if (brightnessChanges >= 3) {
        summerTime = !summerTime;
        brightnessChanges = 0;
    }
}

bool isHappyBirthday(DateTime* now) {
    for (const DateTime& birthday : birthdays) {
        bool sameMonthAndDay = now->day() == birthday.day() && now->month() == birthday.month();
        if (sameMonthAndDay) {
            return true;
        }
    }
    return false;
}