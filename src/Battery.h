#pragma once
#include <BatteryMonitor.h>

#include <cstddef>

#define BAT_GPIO0 0  // Battery voltage

static BatteryMonitor battery(BAT_GPIO0);

struct BatteryPercentageRingBuffer {
  static constexpr uint16_t MAX_SAMPLES = 10;

  uint16_t buf[MAX_SAMPLES];
  uint16_t head = 0;
  uint16_t sum = 0;
  uint16_t prev_val = 0;

  void init(uint16_t value);
  void update(uint16_t value);
  uint16_t evaluate();
};
