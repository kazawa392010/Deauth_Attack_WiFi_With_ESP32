#ifndef UI_H
#define UI_H

#include <Arduino.h>

void ui_init();
void ui_update();
void ui_show_scan();
void ui_show_select(int current_network, int total_networks);
void ui_show_confirm(const char* ssid);
void ui_show_attacking(int eliminated);
void ui_show_stopped(int eliminated);
void ui_clear();
void ui_screen_off();
void ui_screen_on();
void ui_show_rssi_scanner();
void ui_show_networks_with_distance();

int ui_get_state();
void ui_set_state(int state);

#endif
