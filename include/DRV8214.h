#pragma once
#include <Arduino.h>

struct DRV8214_Config {
    uint8_t dummy;
};

class DRV8214 {
public:
    DRV8214(uint8_t, uint8_t, uint16_t, uint16_t, uint8_t, uint8_t, uint16_t);
    void init(DRV8214_Config& cfg);
    void turnXRipples(uint32_t ripples, bool direction, bool enable, uint8_t channel);
};
