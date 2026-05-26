#include <WiFi.h>
#include <U8x8lib.h>
#include "ui.h"
#include "definitions.h"
#include "rssi.h"

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE, /* clock=*/ OLED_SCL, /* data=*/ OLED_SDA);

int8_t ui_state = UI_STATE_SCAN;
uint8_t screen_on = 1;

void ui_init() {
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  
  u8x8.clearDisplay();
  u8x8.drawString(0, 0, "Deauther");
  u8x8.drawString(0, 1, "Init...");
  delay(500);
  
  DEBUG_PRINTLN("UI initialized");
}

void ui_screen_off() {
  if (screen_on) {
    u8x8.clearDisplay();
    u8x8.setPowerSave(1); // Turn off display
    screen_on = 0;
    DEBUG_PRINTLN("Screen OFF - resources focused on attack");
  }
}

void ui_screen_on() {
  if (!screen_on) {
    u8x8.setPowerSave(0); // Turn on display
    screen_on = 1;
    DEBUG_PRINTLN("Screen ON");
  }
}

void ui_show_scan() {
  u8x8.clearDisplay();
  u8x8.drawString(0, 0, "=SCANNING=");
  u8x8.drawString(0, 2, "Finding WiFi");
  u8x8.drawString(0, 3, "networks...");
  u8x8.drawString(0, 5, "Please wait...");
}

void ui_show_select(int current_network, int total_networks) {
  u8x8.clearDisplay();
  u8x8.drawString(0, 0, "=SELECT=");
  
  u8x8.setCursor(0, 2);
  u8x8.print("Net ");
  u8x8.print(current_network + 1);
  u8x8.print("/");
  u8x8.print(total_networks);
  
  String ssid = WiFi.SSID(current_network);
  if (ssid.length() > 14) {
    ssid = ssid.substring(0, 13);
  }
  u8x8.drawString(0, 4, ssid.c_str());
  
  // Display distance based on RSSI
  int8_t rssi = get_network_rssi(current_network);
  float distance = calculate_distance(rssi);
  
  u8x8.setCursor(0, 5);
  u8x8.print("D:");
  u8x8.print((int)distance);
  u8x8.print("m RSSI:");
  u8x8.print(rssi);
  u8x8.print("dB");
  
  u8x8.drawString(0, 6, "[UP] [SELECT]");
}

void ui_show_confirm(const char* ssid) {
  u8x8.clearDisplay();
  u8x8.drawString(0, 0, "=CONFIRM=");
  u8x8.drawString(0, 2, "Attack?");
  
  String ssid_str = String(ssid);
  if (ssid_str.length() > 14) {
    ssid_str = ssid_str.substring(0, 13);
  }
  u8x8.drawString(0, 3, ssid_str.c_str());
  
  u8x8.drawString(0, 5, "YES");
  u8x8.drawString(12, 5, "NO");
}

void ui_show_attacking(int eliminated) {
  u8x8.clearDisplay();
  u8x8.drawString(0, 0, "=ATTACKING=");
  u8x8.drawString(0, 2, "In progress...");
  
  u8x8.setCursor(0, 4);
  u8x8.print("Elim: ");
  u8x8.print(eliminated);
  
  u8x8.drawString(0, 6, "[STOP]");
}

void ui_show_stopped(int eliminated) {
  u8x8.clearDisplay();
  u8x8.drawString(0, 0, "=STOPPED=");
  
  u8x8.setCursor(0, 2);
  u8x8.print("Elim: ");
  u8x8.print(eliminated);
  
  u8x8.drawString(0, 4, "Finished!");
  u8x8.drawString(0, 6, "[SELECT] Scan");
}

void ui_clear() {
  u8x8.clearDisplay();
}

int ui_get_state() {
  return ui_state;
}

void ui_set_state(int state) {
  ui_state = state;
}
