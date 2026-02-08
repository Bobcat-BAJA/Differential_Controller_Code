#pragma once
#include <Arduino.h>

struct DRV8214_Config {
    uint8_t dummy;
};

class DRV8214 {
public:
    DRV8214(
        uint8_t in1_pin,
        uint8_t in2_pin,
        uint8_t pwm_pin,
        uint8_t sleep_pin,
        uint8_t fault_pin,
        uint8_t channel,
        uint16_t pwm_freq
    );
    void init(DRV8214_Config& cfg);
    void turnXRipples(uint32_t ripples, bool direction, bool enable, uint8_t channel);
};
