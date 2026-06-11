#include <Arduino.h> //TODO: pragma once

enum ledstate_t
{
    kSwitchOff,
    kSwitchOn,
    kBlinkOn,
    kBlinkOff,
    kBlinkPause,
    kBreathIn,
    kBreathOut
};

int defaultBlinkDelay_0 = 300;

enum z_ledmode_t
{
    LED_MODE_ON_OFF = 0,
    LED_MODE_TOGGLE = 2,
    LED_MODE_FADE = 3,
    LED_MODE_BLINK_FOREVER = 4,
    LED_MODE_BLINK_PERIOD = 5,
    LED_MODE_BLINK_NUM_TIME = 6,
};

struct ledState_struct
{
    uint8_t id = 0;
    uint8_t blinkOnTime = 0;
    uint8_t blinkOffTime = 0;
    uint16_t blinkTimePeriod = 300;
    uint8_t blinkNumberOfTimes = 0;
    uint32_t prevMillis = 0;
    bool isLedOn = false;
    z_ledmode_t mode = LED_MODE_ON_OFF;
};

class ZalcLED
{
private:
    uint8_t m_led_counts = 8;
    uint32_t ledsPinLastState;                       // B010001110 - on/off
    uint32_t ledsPinCurrentState = ledsPinLastState; // B010001110 - on/off

    ledState_struct ledsState2[8];

    uint32_t currentMillis = millis();
    uint32_t prevMillis = 0;

    uint16_t blinkDelay = 300;

public:
    int dataPin;
    int latchPin;
    int clockPin;
    int leds = B00000000;

    ZalcLED()
    {
        for (int i = 0; i < 8; i++)
        {
            ledsState2[i].id = i;
        }
    }

    void init(int dataPin1, int latchPin1, int clockPin1)
    {
        dataPin = dataPin1;
        latchPin = latchPin1;
        clockPin = clockPin1;

        pinMode(latchPin, OUTPUT);
        pinMode(clockPin, OUTPUT);
        pinMode(dataPin, OUTPUT);
        digitalWrite(latchPin, HIGH);
    }

    void onAll()
    { // on all leds
        for (int i = 0; i < sizeof(ledsState2); i++)
        {
            ledsState2[i].mode = LED_MODE_ON_OFF;
        }
    }

    void offAll()
    { // off all leds
        for (int i = 0; i < sizeof(ledsState2); i++)
        {
            ledsState2[i].isLedOn = false;
        }
    }

    void on(int ledNumber)
    { // on led with ledNumber
        onBit(ledNumber);
        ledsState2[ledNumber].isLedOn = true;
        ledsState2[ledNumber].mode = LED_MODE_ON_OFF;
    }

    void off(int ledNumber)
    { // off led with ledNumber
        offBit(ledNumber);
        ledsState2[ledNumber].isLedOn = false;
        ledsState2[ledNumber].mode = LED_MODE_ON_OFF;
    }

    void blink1(int ledNumber)
    { // blink ledNumber on/off 300/300ms
        ledsState2[ledNumber].mode = LED_MODE_BLINK_FOREVER;
    }

    // TODO: custom blink time - now not working
    void blink1(int ledNumber, uint16_t ledBlinkDelay)
    {
        ledsState2[ledNumber].mode = LED_MODE_BLINK_FOREVER;
        ledsState2[ledNumber].blinkTimePeriod = ledBlinkDelay;
    }

    void ZalcLED::toggle()
    {
    }

    unsigned int getPinState(int pinNumber)
    {
        return ledsState2[pinNumber].isLedOn;
    }

    void loop()
    {
        currentMillis = millis();
        if (ledsPinCurrentState != ledsPinLastState)
        {
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, LSBFIRST, ledsPinLastState);
            digitalWrite(latchPin, HIGH);
        }

        int newLeds = 0;
        int length = sizeof(ledsState2) / sizeof(ledsState2[0]);

        for (int i = 0; i < length; i++)
        {
            newLeds <<= 1;

            // TODO:
            switch (ledsState2[i].mode)
            {
            case LED_MODE_ON_OFF:
                newLeds = newLeds | 0b00000001;
                break;

            case LED_MODE_BLINK_FOREVER:
                uint32_t blinkDelay3 = ledsState2[i].blinkTimePeriod; // TODO: custom blink time!!!!!!!!!!!!!!!!!!!!!!!!!
                if ((currentMillis - ledsState2[i].prevMillis) >= ledsState2[i].blinkTimePeriod)
                {
                    if (isLedOn(i))
                    {
                        newLeds &= 0b11111110;
                    }
                    else
                    {
                        newLeds = newLeds | 0b00000001;
                    }
                }
                else
                {
                    // save previous state of Led
                    if (isLedOn(i))
                    {
                        newLeds = newLeds | 0b00000001;
                    }
                    else
                    {
                        newLeds &= 0b11111110;
                    }
                }
                break;

            default: // LED_MODE_OFF // newLeds |= 0;
                break;
            }

            if ((currentMillis - ledsState2[i].prevMillis) >= ledsState2[i].blinkTimePeriod)
            {
                ledsState2[i].prevMillis = currentMillis;
            }
        }

        ledsPinCurrentState = newLeds;
        if (newLeds != ledsPinLastState)
        {
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, LSBFIRST, newLeds);
            digitalWrite(latchPin, HIGH);
            ledsPinLastState = newLeds;
        }

        // FIXME: custom blink time - change blink delay
        if ((currentMillis - prevMillis) >= blinkDelay)
        // if ((currentMillis - prevMillis) >= ledsState2[i].blinkTimePeriod)
        {
            prevMillis = currentMillis;
        }
    }

private:
    unsigned long previousMillis = 0;
    unsigned long changetBit = B00000000;
    void onBit(int bitNumber)
    {
        changetBit = (1 << (m_led_counts - 1 - bitNumber)); // Установили bitNumber-й (3) бит: 00001000 (8)
        leds = leds | changetBit;
        ledsPinCurrentState = ledsPinCurrentState | changetBit;
    }

    void offBit(int bitNumber)
    {
        changetBit = (1 << (m_led_counts - 1 - bitNumber)); // Установили bitNumber-й (3) бит: 00001000 (8)
        leds = leds & ~changetBit;
        ledsPinCurrentState = ledsPinCurrentState & ~changetBit;
        // leds ^= (1 << 7 - bitNumber);  // Установили bitNumber-й бит: 00001000 (8)
    }

    bool isLedOn(int ledNumber)
    {
        uint8_t shiftedByte = ledsPinLastState >> (m_led_counts - 1 - ledNumber);
        return (shiftedByte & 1) != 0;
    }

    char getBits(unsigned int n)
    {
        char str;

        for (int i = 1; i <= sizeof(n); i++)
        {
            int bit = (n >> i) & 1; // Сдвигаем и проверяем последний бит
            str += bit;
        }
        return str;
    }

    void printBits(unsigned int n)
    {

        Serial.print("Bit is: ");
        for (int i = sizeof(n); i > 0; i--)
        {
            int bit = (n >> i) & 1; // Сдвигаем и проверяем последний бит
            Serial.print(bit);
        }
        Serial.println(' :END');
    }
};
