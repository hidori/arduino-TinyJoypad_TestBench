// TinyJoypad_TestBench

#include <Arduino.h>
#include "tinyjoypadUtils.h"

#define USE_DISPLAY

#ifdef USE_DISPLAY
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_COLOR_WHITE SSD1306_WHITE
#endif

#define SOUND_TONE 262
#define SOUND_DURATION 200

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  InitTinyJoypad();
#ifdef USE_DISPLAY
  InitDisplay();
#endif

  Sound(SOUND_TONE, SOUND_DURATION);
  _delay_ms(200);

  printGreeting();
}

void loop() {
  if (isFirePressed()) {
    printButton("FIRE");
  }

  if (isLeftPressed()) {
    printButton("LEFT");
  }

  if (isRightPressed()) {
    printButton("RIGHT");
  }

  if (isUpPressed()) {
    printButton("UP");
  }

  if (isDownPressed()) {
    printButton("DOWN");
  }

  digitalWrite(LED_BUILTIN, LOW);
  _delay_ms(100);
}

void printGreeting() {
  serialPrintln("TinyJoypad_TestBench");
  serialPrintln("Press any button to test.");
  serialPrintln("Press 'FIRE' to exit.");
  serialPrintln("Press 'LEFT' to test the left button.");
  serialPrintln("Press 'RIGHT' to test the right button.");
  serialPrintln("Press 'UP' to test the up button.");
  serialPrintln("Press 'DOWN' to test the down button.");

#ifdef USE_DISPLAY
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(DISPLAY_COLOR_WHITE);
  display.setCursor(4, 28);
  display.print("TinyJoypad_TestBench");
  display.display();
  _delay_ms(3000);


  for (int x = 0; x < DISPLAY_WIDTH; x++) {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      display.drawPixel(x, y, DISPLAY_COLOR_WHITE);
    }
    display.display();
    _delay_ms(10);
  }
  _delay_ms(3000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(DISPLAY_COLOR_WHITE);
  display.setCursor(18, 28);
  display.print("Press any button");
  display.display();
#endif
}

void printButton(const char *label) {
  digitalWrite(LED_BUILTIN, HIGH);

  Sound(SOUND_TONE, SOUND_DURATION);
  digitalWrite(LED_BUILTIN, HIGH);

  serialPrintln(label);

#ifdef USE_DISPLAY
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(DISPLAY_COLOR_WHITE);
  display.setCursor(0, 0);
  display.print(label);
  display.display();
#endif
  _delay_ms(200);
}
