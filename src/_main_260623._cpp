// #include <cstring> // для std::memcpy
// #include <vector>

// #include <iostream>
// #include <bitset>
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

// enum z_ledstate_t
// {
//   LED_OFF = 0,
//   LED_ON = 1,
// };

// int defaultBlinkDelay_01 = 300;

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
  // uint8_t count;
  uint8_t blinkOnTime = 0;
  uint8_t blinkOffTime = 0;
  // uint8_t blinkTimePeriod = defaultBlinkDelay_0;
  uint16_t blinkTimePeriod = 300;
  uint8_t blinkNumberOfTimes = 0;
  uint32_t prevMillis = 0;
  bool isLedOn = false;
  z_ledmode_t mode = LED_MODE_ON_OFF;
  // z_ledstate_t state = LED_OFF;
};

class Foo
{
private:
  uint8_t m_led_counts = 8;
  // uint8_t m_pin;
  // uint8_t m_lo;
  // uint8_t m_hi;
  // uint8_t m_count;
  // uint32_t m_start;
  // uint32_t m_interval = 300;
  // ledstate_t m_state;
  uint32_t ledsPinLastState;                       // B010001110 - on/off
  uint32_t ledsPinCurrentState = ledsPinLastState; // B010001110 - on/off
  // z_ledstate_t ledsState[m_led_counts] {LED_MODE_OFF};
  // z_ledstate_t ledsState[8]{};

  ledState_struct ledsState2[8];

  uint32_t currentMillis = millis();
  uint32_t prevMillis = 0;

  // int defaultBlinkDelay = 300;
  uint16_t blinkDelay = 300;

  // for (int i =0; i < sizeof(ledsState); i++) {
  //   ledsState[i] = LED_MODE_OFF;
  // }
public:
  int var; // переменная (свойство)
  int dataPin;
  int latchPin;
  int clockPin;
  int leds = B00000000;

  Foo()
  {
    for (int i = 0; i < 8; i++)
    {
      ledsState2[i].id = i;
    }
  }

  // void toggle();

  void init(int dataPin1, int latchPin1, int clockPin1)
  {
    dataPin = dataPin1;
    latchPin = latchPin1;
    clockPin = clockPin1;

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    // ставим HIGH на "защёлку", чтобы регистр не принимал сигнал
    digitalWrite(latchPin, HIGH);
  }

  void onAll()
  { // on all leds
    // for (int i = 0; i < sizeof(ledsState); i++)
    for (int i = 0; i < sizeof(ledsState2); i++)
    {
      // ledsState[i] = LED_ON;
      // ledsState2[i].state = LED_ON;
      ledsState2[i].mode = LED_MODE_ON_OFF;
    }

    // digitalWrite(latchPin, LOW);                                        // ставим LOW на "защёлку"
    // shiftOut(dataPin, clockPin, LSBFIRST, B11111111); // отправляем байт в двоичном виде
    // digitalWrite(latchPin, HIGH);                                       // ставим HIGH на "защёлку"
  }

  void offAll()
  { // off all leds
    // for (int i = 0; i < sizeof(ledsState); i++)
    for (int i = 0; i < sizeof(ledsState2); i++)
    {
      // ledsState[i] = LED_OFF;
      // ledsState2[i].state = LED_OFF;
      ledsState2[i].isLedOn = false;
    }
  }

  void on(int ledNumber)
  { // on led with ledNumber
    onBit(ledNumber);
    // ledsState[ledNumber] = LED_ON;
    // ledsState2[ledNumber].state = LED_ON;
    ledsState2[ledNumber].isLedOn = true;
    ledsState2[ledNumber].mode = LED_MODE_ON_OFF;
  }

  void off(int ledNumber)
  { // off led with ledNumber
    offBit(ledNumber);
    // ledsState[ledNumber] = LED_OFF;
    // ledsState2[ledNumber].state = LED_OFF;
    ledsState2[ledNumber].isLedOn = false;
    ledsState2[ledNumber].mode = LED_MODE_ON_OFF;
  }

  void blink1(int ledNumber)
  { // blink ledNumber on/off 300/300ms
    // ledsState[ledNumber] = LED_MODE_BLINK_FOREVER;
    ledsState2[ledNumber].mode = LED_MODE_BLINK_FOREVER;
  }

  // TODO: custom blink time - now not working
  void blink1(int ledNumber, uint16_t ledBlinkDelay)
  {
    ledsState2[ledNumber].mode = LED_MODE_BLINK_FOREVER;
    ledsState2[ledNumber].blinkTimePeriod = ledBlinkDelay;
  }

  void Foo::toggle()
  {
  }

  unsigned int getPinState(int pinNumber)
  {
    // return ledsState[pinNumber];
    return ledsState2[pinNumber].isLedOn;
  }

  void loop()
  {
    // int blinkDelay = 1500;          // ms blink delay
    // int blinkDelay = defaultBlinkDelay_0; // ms blink delay
    currentMillis = millis();
    if (ledsPinCurrentState != ledsPinLastState)
    {
      // todo: switch 74hcPins
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, ledsPinLastState);
      digitalWrite(latchPin, HIGH);
    }

    int newLeds = 0;
    // int length = sizeof(ledsState) / sizeof(ledsState[0]);
    int length = sizeof(ledsState2) / sizeof(ledsState2[0]);

    for (int i = 0; i < length; i++)
    {
      newLeds <<= 1;

      // TODO:
      // switch (ledsState[i])
      switch (ledsState2[i].mode)
      {
      case LED_MODE_ON_OFF:
        newLeds = newLeds | 0b00000001;
        // ledsState2[i].blinkTimePeriod = blinkDelay;
        break;

        // case LED_MODE_TOGGLE:
        //   // if (ledsState[i] == LED_MODE_ON)
        //   if (ledsState2[i].state == LED_ON)
        //   {
        //     ledsState[i] = LED_OFF; // TODO: del it
        //     ledsState2[i].state = LED_OFF;
        //   }
        //   // else if (ledsState[i] == LED_MODE_OFF)
        //   else if (ledsState2[i].state == LED_OFF)
        //   {
        //     ledsState[i] = LED_ON; // TODO: del it
        //     ledsState2[i].state = LED_ON;
        //     // newLeds |= 1;
        //     newLeds = newLeds | 0b00000001;
        //   }
        //   break;

      case LED_MODE_BLINK_FOREVER:
        uint32_t blinkDelay3 = ledsState2[i].blinkTimePeriod; // TODO: custom blink time!!!!!!!!!!!!!!!!!!!!!!!!!
        // if ((currentMillis - prevMillis) >= blinkDelay3)
        if ((currentMillis - ledsState2[i].prevMillis) >= ledsState2[i].blinkTimePeriod)
        {
          // Serial.println("Blink...............");
          if (isLedOn(i))
          {
            // Serial.print("OFF time: ");
            // Serial.println(millis());
            newLeds &= 0b11111110;
          }
          else
          {
            // Serial.print("ON time: ");
            // Serial.println(millis());
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
        // Serial.print("Pin N: ");
        // Serial.print(i);
        // Serial.println(" - case default - LED_MODE_OFF");
        // newLeds &= 0;
        // Code block for no match (optional)
        break;
      }

      // if ((currentMillis - prevMillis) >= blinkDelay)
      if ((currentMillis - ledsState2[i].prevMillis) >= ledsState2[i].blinkTimePeriod)
      {
        ledsState2[i].prevMillis = currentMillis;
      }
    }

    ledsPinCurrentState = newLeds;
    if (newLeds != ledsPinLastState)
    {
      // todo: switch 74hcPins
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, newLeds);
      digitalWrite(latchPin, HIGH);
      ledsPinLastState = newLeds;
    }

    // if ((millis() - prevMillis) >= blinkDelay) {
    // prevMillis = millis();

    // TODO: del it
    // FIXME: custom blink time - change blink delay
    if ((currentMillis - prevMillis) >= blinkDelay)
    // if ((currentMillis - prevMillis) >= ledsState2[i].blinkTimePeriod)
    {
      prevMillis = currentMillis;
    }

    // Serial.print(" - end getBits(newLeds): ");
    // Serial.println(getBits(newLeds));
    // printBits(newLeds);
    // digitalWrite(latchPin, LOW);
    //   shiftOut(dataPin, clockPin, LSBFIRST, ~newLeds);
    //   digitalWrite(latchPin, HIGH);
  }

private:
  unsigned long previousMillis = 0;
  // unsigned long currentMillis = millis();
  unsigned long changetBit = B00000000;
  // системный код
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
    // char str;

    Serial.print("Bit is: ");
    // for (int i = 1; i <= sizeof(n); i++) {
    for (int i = sizeof(n); i > 0; i--)
    {
      int bit = (n >> i) & 1; // Сдвигаем и проверяем последний бит
      // str += bit;
      Serial.print(bit);
    }
    Serial.println(' :END');
  }
};

#include <ezLED.h> // ezLED library
#include <MyClass.h>
#include <zalcLED.h>

#define dataPin 6  // пин подключен к входу DS
#define latchPin 5 // пин подключен к входу ST_CP
#define clockPin 4 // пин подключен к входу SH_CP
#define btnBluePin 11
#define btnYellowPin 10

// Foo foo;
zalcLED foo;

ezLED ledBlue(12);   // create a LED object that attach to pin 12
ezLED ledYellow(13); // create a LED object that attach to pin 13

MyClass obj(2);

void setup()
{
  Serial.begin(9600);
  pinMode(btnBluePin, INPUT);
  pinMode(btnYellowPin, INPUT);

  // foo.var = 123; // обращение к переменной объекта foo
  // foo.func();     // вызов метода объекта foo
  foo.init(dataPin, latchPin, clockPin);

  // pinMode(latchPin, OUTPUT);
  // pinMode(clockPin, OUTPUT);
  // pinMode(dataPin, OUTPUT);
  // // ставим HIGH на "защёлку", чтобы регистр не принимал сигнал
  // digitalWrite(latchPin, HIGH);
  ledYellow.blink(250, 750);
}

void loop()
{
  // Serial.println("");
  // Serial.println("");
  // Serial.println("--------------loop start");
  ledBlue.loop();
  ledYellow.loop();
  foo.loop();

  int buttonBlueState = digitalRead(btnBluePin);
  int buttonYellowState = digitalRead(btnYellowPin);

  if (buttonBlueState == HIGH)
  {
    ledBlue.turnON(); // turn on immediately
    // led.turnON(1000); // turn on after 1 second
    foo.off(1);
    // foo.blink1(2);
    foo.off(2);
    foo.blink1(3);
    // foo.blink1(4);
    foo.blink1(4, 100);
    // delay(300);
    // if (foo.getState(3) == LED_MODE_BLINK_FOREVER) {
    // Serial.print("STATE3 ON: ");
    // Serial.println(foo.getPinState(3));
    // ledYellow.blink(250, 750);       // turn on immediately
    // }
  }
  else
  {
    ledBlue.turnOFF(); // turn off immediately
    // led.turnOFF(1000); // turn off after 1 second
    foo.on(1);
    foo.on(2);
    foo.on(3);
    foo.on(4);
    // Serial.print("STATE3 OFF: ");
    // Serial.println(foo.getPinState(3));
    // delay(300);
  }

  if (buttonYellowState == HIGH)
  {
    if (ledYellow.getState() == LED_IDLE)
    {
      Serial.println("BLINKING");
      ledYellow.blink(250, 750); // turn on immediately
    }
  }
  else
  {
    if (ledYellow.getState() == LED_BLINKING)
    {
      Serial.println("BLINK ENDED2");   // ledYellow.cancel();       // turn off immediately
      Serial.print("MyClass multi = "); // ledYellow.cancel();       // turn off immediately
      Serial.println(obj.multi2());     // ledYellow.cancel();       // turn off immediately
      ledYellow.cancel();
    }
    // led.turnOFF(1000); // turn off after 1 second
  }

  // Serial.println("--------------loop end");
  // delay(100);

  //------------------------------------------------------------
  // if (ledYellow.getState() == LED_BLINKING)
  //   Serial.println("BLINKING");
  // else if (ledYellow.getState() == LED_IDLE)
  //   Serial.println("BLINK ENDED");

  // ledBlue.turnON(1000);
  // delay(300);
  // ledBlue.turnOFF(1000); // turn off after 1 second
  // delay(300);

  // if (ledBlue.getOnOff() == LED_ON)
  //   Serial.println("LED is ON");
  // else
  //   Serial.println("LED is OFF");

  // digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED on
  // delay(500);                      // Wait for a second
  // digitalWrite(LED_BUILTIN, LOW);   // Turn the LED off
  // delay(100);                      // Wait for a second

  // digitalWrite(latchPin, LOW);                                        // ставим LOW на "защёлку"
  // shiftOut(dataPin, clockPin, LSBFIRST, 0b11110000); // отправляем байт в двоичном виде
  // digitalWrite(latchPin, HIGH);                                       // ставим HIGH на "защёлку"
  // delay(500); // задержка в 1 секунду
  // digitalWrite(latchPin, LOW);                                        // ставим LOW на "защёлку"
  // shiftOut(dataPin, clockPin, LSBFIRST, 0b00001111); // отправляем байт в двоичном виде
  // digitalWrite(latchPin, HIGH);                                       // ставим HIGH на "защёлку"
  // delay(1500); // задержка в 1 секунду

  //   foo.offAll();
  //   delay(300);
  //   foo.onAll();
  //   delay(300);

  //   foo.offAll();
  //   delay(300);
  //   foo.onAll();
  //   delay(300);

  //   foo.offAll();
  //   delay(300);
  //   foo.onAll();
  //   delay(300);
  //   foo.offAll();
  //   delay(500);

  //-----------------------------------
  // foo.on(4);
  // delay(100);
  // foo.on(5);
  // delay(300);

  // foo.off(4);
  // delay(100);
  // foo.off(5);
  // delay(300);
}
