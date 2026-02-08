#include "DRV8214.h"

DRV8214::DRV8214(
    uint8_t i2cAddr,
    uint8_t instance,
    uint16_t maxCurrent,
    uint16_t rippleCount,
    uint8_t mode,
    uint8_t channel,
    uint16_t timeout
)
{
}

void DRV8214::init(DRV8214_Config& cfg)
{
}

void DRV8214::turnXRipples(
    uint32_t ripples,
    bool direction,
    bool enable,
    uint8_t channel
)
{
}