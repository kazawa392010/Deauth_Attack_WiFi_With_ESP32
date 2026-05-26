#include <Arduino.h>
#include "buttons.h"
#include "definitions.h"

volatile unsigned long last_up_press = 0;
volatile unsigned long last_select_press = 0;
volatile bool up_pressed = false;
volatile bool select_pressed = false;

void IRAM_ATTR button_up_isr() {
  unsigned long now = millis();
  if (now - last_up_press > BUTTON_DEBOUNCE) {
    up_pressed = true;
    last_up_press = now;
  }
}

void IRAM_ATTR button_select_isr() {
  unsigned long now = millis();
  if (now - last_select_press > BUTTON_DEBOUNCE) {
    select_pressed = true;
    last_select_press = now;
  }
}

void buttons_init() {
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_UP), button_up_isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_SELECT), button_select_isr, FALLING);
  
  DEBUG_PRINTLN("Buttons initialized");
}

bool button_up_pressed() {
  if (up_pressed) {
    up_pressed = false;
    return true;
  }
  return false;
}

bool button_select_pressed() {
  if (select_pressed) {
    select_pressed = false;
    return true;
  }
  return false;
}

void buttons_update() {
  // ISR handles everything
}
