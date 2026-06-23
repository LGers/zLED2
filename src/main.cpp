#include <Arduino.h>

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
}
