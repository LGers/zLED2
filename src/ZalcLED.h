#include <Arduino.h> //TODO: pragma once

#ifndef ZALCLED_H
#define ZALCLED_H

class ZalcLED {
private:
    int data;

public:
    ZalcLED(int val); // Конструктор
    void printData(); // Метод вывода
    int multi2(); // Метод вывода

    void init(int dataPin1, int latchPin1, int clockPin1);
    void onAll();
    void offAll();
    void on(int ledNumber);
    void off(int ledNumber);

    void blink1(int ledNumber);
    void blink1(int ledNumber, uint16_t ledBlinkDelay);
    void ZalcLED::toggle();

    unsigned int getPinState(int pinNumber);

    void loop();

};

#endif