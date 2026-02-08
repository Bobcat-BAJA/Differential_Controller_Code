#pragma once

#include <Arduino.h>

struct DRV8214_Config {
    uint8_t dummy;
};

class DRV8214 {
public:
    // Constructor
    DRV8214(
        uint8_t i2cAddr,
        uint8_t instance,
        uint16_t maxCurrent,
        uint16_t rippleCount,
        uint8_t mode,
        uint8_t channel,
        uint16_t timeout
    );

    // API
    void init(DRV8214_Config& cfg);
    void turnXRipples(
        uint32_t ripples,
        bool direction,
        bool enable,
        uint8_t channel
    );
};

