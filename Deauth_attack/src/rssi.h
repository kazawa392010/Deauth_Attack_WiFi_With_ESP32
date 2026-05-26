#ifndef RSSI_H
#define RSSI_H

#include <Arduino.h>

// WiFi network info with distance
typedef struct {
  char ssid[33];        // 32 byte SSID + null terminator
  uint8_t rssi;         // Signal strength (as int8_t but stored as uint8_t)
  float distance;       // Estimated distance in meters
  uint8_t channel;      // WiFi channel
} wifi_network_dist_t;

// Calculate distance from RSSI
float calculate_distance(int8_t rssi);

// Get RSSI value for a network
int8_t get_network_rssi(int network_index);

#endif
