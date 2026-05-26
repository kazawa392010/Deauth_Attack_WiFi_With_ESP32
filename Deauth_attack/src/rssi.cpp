#include <WiFi.h>
#include <cmath>
#include "rssi.h"
#include "definitions.h"

// TX Power at 1m reference distance (dBm)
#define TX_POWER_REF -59

// Path loss exponent (2.0 = free space, 2.5-4 = with obstacles)
#define PATH_LOSS_EXPONENT 2.2

float calculate_distance(int8_t rssi) {
  if (rssi == 0) return 0.0;
  
  // Distance = 10 ^ ((TX_POWER - RSSI) / (10 * N))
  float numerator = TX_POWER_REF - rssi;
  float exponent = numerator / (10.0f * PATH_LOSS_EXPONENT);
  
  float distance = pow(10.0f, exponent);
  
  // Clamp to reasonable values (0.1m to 200m)
  if (distance < 0.1f) distance = 0.1f;
  if (distance > 200.0f) distance = 200.0f;
  
  return distance;
}

int8_t get_network_rssi(int network_index) {
  return WiFi.RSSI(network_index);
}
