#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

void buttons_init();
bool button_up_pressed();
bool button_select_pressed();
void buttons_update();

#endif
