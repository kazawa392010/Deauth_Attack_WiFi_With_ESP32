#ifndef DEAUTH_H
#define DEAUTH_H

#include <Arduino.h>

void start_deauth(int wifi_number, int attack_type, uint16_t reason);
void stop_deauth();

extern volatile uint16_t eliminated_stations;
extern uint8_t deauth_type;

#endif