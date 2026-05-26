#include <WiFi.h>
#include <U8x8lib.h>
#include "rssi.h"
#include "definitions.h"

extern U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8;

void ui_show_rssi_scanner() {
  u8x8.clearDisplay();
  u8x8.drawString(0, 0, "=RSSI SCANNER=");
  
  int num_networks = WiFi.scanNetworks();
  if (num_networks > MAX_NETWORKS_DISPLAY) {
    num_networks = MAX_NETWORKS_DISPLAY;
  }
  
  // Display up to 4 networks with distances
  for (uint8_t i = 0; i < num_networks && i < 4; i++) {
    u8x8.setCursor(0, i + 1);
    
    // Network number
    u8x8.print(i + 1);
    u8x8.print(".");
    
    // SSID (truncate to 7 chars)
    String ssid = WiFi.SSID(i);
    if (ssid.length() > 7) {
      ssid = ssid.substring(0, 7);
    }
    u8x8.print(ssid.c_str());
    u8x8.print(" ");
    
    // Distance
    int8_t rssi = get_network_rssi(i);
    float distance = calculate_distance(rssi);
    u8x8.print((int)distance);
    u8x8.print("m");
  }
  
  u8x8.setCursor(0, 6);
  u8x8.print("Found: ");
  u8x8.print(num_networks);
  u8x8.print(" networks");
}

void ui_show_networks_with_distance() {
  int num_networks = WiFi.scanNetworks();
  if (num_networks > MAX_NETWORKS_DISPLAY) {
    num_networks = MAX_NETWORKS_DISPLAY;
  }
  
  DEBUG_PRINTLN("\n=== WiFi Networks (with Distance) ===");
  for (uint8_t i = 0; i < num_networks; i++) {
    String ssid = WiFi.SSID(i);
    int8_t rssi = get_network_rssi(i);
    float distance = calculate_distance(rssi);
    
    DEBUG_PRINTF("%d. SSID: %-32s | RSSI: %3ddBm | Distance: %6.2fm\n", 
      i + 1, ssid.c_str(), rssi, distance);
  }
  DEBUG_PRINTLN("=====================================\n");
}
