#include <stdint.h>
#include <Arduino.h>

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

enum z_ledstate_t
{
  LED_MODE_OFF = 0,
  LED_MODE_ON = 1,
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
  uint8_t blinkTimePeriod = 0;
  uint8_t blinkNumberOfTimes = 0;
  uint32_t prevMillis = 0;
};

class ZalcLED
{
private:
  uint8_t m_led_counts = 8;
  uint8_t m_pin;
  uint8_t m_lo;
  uint8_t m_hi;
  uint8_t m_count;
  uint32_t m_start;
  uint32_t m_interval = 300;
  ledstate_t m_state;
  uint32_t ledsPinLastState;                       // B010001110 - on/off
  uint32_t ledsPinCurrentState = ledsPinLastState; // B010001110 - on/off
  z_ledstate_t ledsState[8]{};

  uint32_t currentMillis = millis();
  uint32_t prevMillis = 0;

public:
  int dataPin;
  int latchPin;
  int clockPin;
  int leds = B00000000;

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
    for (int i = 0; i < sizeof(ledsState); i++)
    {
      ledsState[i] = LED_MODE_ON;
    }
  }

  void offAll()
  { // off all leds
    for (int i = 0; i < sizeof(ledsState); i++)
    {
      ledsState[i] = LED_MODE_OFF;
    }
  }

  void on(int ledNumber)
  { // on led with ledNumber
    onBit(ledNumber);
    ledsState[ledNumber] = LED_MODE_ON;
  }

  void off(int ledNumber)
  { // off led with ledNumber
    offBit(ledNumber);
    ledsState[ledNumber] = LED_MODE_OFF;
  }

  void blink1(int ledNumber)
  { // blink ledNumber on/off 300/300ms
    ledsState[ledNumber] = LED_MODE_BLINK_FOREVER;
  }

  void Foo::toggle()
  {
    // if (m_state == kSwitchOn) {
    //   digitalWrite(m_pin, m_lo);
    //   m_state = kSwitchOff;
    // } else {
    //   digitalWrite(m_pin, m_hi);
    //   m_state = kSwitchOn;
    // }
  }

  unsigned int getPinState(int pinNumber)
  {
    return ledsState[pinNumber];
  }

  void loop()
  {
    const uint8_t blinkDelay = 300; // ms blink delay
    currentMillis = millis();
    if (ledsPinCurrentState != ledsPinLastState)
    {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, ledsPinLastState);
      digitalWrite(latchPin, HIGH);
    }

    int newLeds = 0;
    int length = sizeof(ledsState) / sizeof(ledsState[0]);

    for (int i = 0; i < length; i++)
    {
      newLeds <<= 1;

      switch (ledsState[i])
      {
      case LED_MODE_ON:
        newLeds = newLeds | 0b00000001;
        break;

      case LED_MODE_TOGGLE:
        if (ledsState[i] == LED_MODE_ON)
        {
          ledsState[i] = LED_MODE_OFF; // newLeds &= 0;
        }
        else if (ledsState[i] == LED_MODE_OFF)
        {
          ledsState[i] = LED_MODE_ON; // newLeds |= 1;
          newLeds = newLeds | 0b00000001;
        }
        break;

      case LED_MODE_BLINK_FOREVER:
        if ((currentMillis - prevMillis) >= 1500)
        {
          Serial.println("Blink...............");
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

      default: // LED_MODE_OFF
        break;
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

    if ((currentMillis - prevMillis) >= 1500)
    {
      prevMillis = currentMillis;
    }
  }

private:
  unsigned long previousMillis = 0;
  unsigned long changetBit = B00000000;

  void onBit(int bitNumber)
  {
    changetBit = (1 << (m_led_counts - 1 - bitNumber));
    leds = leds | changetBit;
    ledsPinCurrentState = ledsPinCurrentState | changetBit;
  }

  void offBit(int bitNumber)
  {
    changetBit = (1 << (m_led_counts - 1 - bitNumber));
    leds = leds & ~changetBit;
    ledsPinCurrentState = ledsPinCurrentState & ~changetBit;
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
      int bit = (n >> i) & 1;
      str += bit;
    }
    return str;
  }
};
