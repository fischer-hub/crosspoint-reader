#include "Battery.h"

void BatteryPercentageRingBuffer::init(uint16_t v) {
  for (size_t i = 0; i < MAX_SAMPLES; i++) {
    buf[i] = v;
  }
  sum = v * MAX_SAMPLES;
  prev_val = v;
  head = 0;
}

void BatteryPercentageRingBuffer::update(uint16_t v) {
  // Previous percentage is set > 100 only if buffer was constructed but not initialized yet
  if (prev_val > 100) {
    init(v);
  }

  // Recalculate rolling sum
  sum -= buf[head];
  buf[head] = v;
  sum += v;

  // Shift head
  head++;
  if (head >= MAX_SAMPLES) head = 0;
}

uint16_t BatteryPercentageRingBuffer::evaluate() {
  // We 'round' (only works for pos numbers but oh well good enough for battery percentages) to an int
  float avg = (sum / MAX_SAMPLES) + 0.5;
  uint16_t new_val = (int)avg;

  // Battery percentage should not increase when not charging so we just cap it to be lower than the last value
  if (new_val < prev_val) {
    prev_val = new_val;
    return new_val;
  } else {
    return prev_val;
  }
}
