#pragma once
#include <Arduino.h>

struct DRV8214_Config {
    uint8_t dummy;
};

class DRV8214 {
public:
    DRV8214(uint8_t i2c_addr,
            uint8_t instance,
            uint16_t ipropi_resistor,
            uint16_t num_ripples,
            uint8_t fault_pin,
            uint8_t enable_pin,
            uint16_t pwm_freq);

    void init(DRV8214_Config& cfg);
    void turnXRipples(uint32_t ripples, bool direction, bool enable, uint8_t channel);
};
