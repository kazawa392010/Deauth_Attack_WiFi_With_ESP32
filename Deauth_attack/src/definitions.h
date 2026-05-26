#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define AP_SSID "ESP32-Deauther"
#define AP_PASS "esp32wroom32"
#define LED 2
#define SERIAL_DEBUG
#define CHANNEL_MAX 13
#define NUM_FRAMES_PER_DEAUTH 16
#define DEAUTH_BLINK_TIMES 2
#define DEAUTH_BLINK_DURATION 20
#define DEAUTH_TYPE_SINGLE 0
#define DEAUTH_TYPE_ALL 1
#define MAX_NETWORKS_DISPLAY 4  // Only display first 4 networks

// Button pins
#define BUTTON_UP 13      // Changed from 35
#define BUTTON_SELECT 12  // Changed from 34

// OLED I2C pins (for U8x8)
#define OLED_SDA 21
#define OLED_SCL 22

// Button debounce time (ms)
#define BUTTON_DEBOUNCE 50

// UI States
#define UI_STATE_SCAN 0
#define UI_STATE_SELECT 1
#define UI_STATE_CONFIRM 2
#define UI_STATE_ATTACKING 3
#define UI_STATE_STOPPED 4

#ifdef SERIAL_DEBUG
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#define DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__)
#endif
#ifndef SERIAL_DEBUG
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#define DEBUG_PRINTF(...)
#endif
#ifdef LED
#define BLINK_LED(num_times, blink_duration) blink_led(num_times, blink_duration)
#endif
#ifndef LED
#define BLINK_LED()
#endif

void blink_led(int num_times, int blink_duration);

#endif