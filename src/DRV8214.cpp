#include "DRV8214.h"

DRV8214::DRV8214(uint8_t i2c_addr,
                 uint8_t instance,
                 uint16_t ipropi_resistor,
                 uint16_t num_ripples,
                 uint8_t fault_pin,
                 uint8_t enable_pin,
                 uint16_t pwm_freq)
{
    // Stub constructor — does nothing
}

void DRV8214::init(DRV8214_Config& cfg)
{
    // Stub init — does nothing
}

void DRV8214::turnXRipples(uint32_t ripples, bool direction, bool enable, uint8_t channel)
{
    // Stub motor command — does nothing
}
