#include "motor_driver.h"
#include <Wire.h>
#include <DRV8214.h>

// --------- Configure your motor here ---------
#define IPROPI_RESISTOR 3600   // matches your hardware
#define NUM_RIPPLES 156        // your motor-specific ripple count

// Create the driver instance
DRV8214 motorDriver(0x60, 0, IPROPI_RESISTOR, NUM_RIPPLES, 0, 1, 3000);
DRV8214_Config driver_config;

// Track motor state
static bool motorMoving = false;

void motor_driver_init(void)
{
    Wire.begin();
    motorDriver.init(driver_config);
    motorMoving = false;
}

void motor_driver_command(motor_command_t dir)
{
    switch (dir)
    {
        case MOTOR_FORWARD:
            motorDriver.turnXRipples(50000, true, true, 1); // forward
            motorMoving = true;
            break;

        case MOTOR_REVERSE:
            motorDriver.turnXRipples(50000, false, true, 1); // reverse
            motorMoving = true;
            break;

        case MOTOR_STOP:
        default:
            motor_driver_stop();
            break;
    }
}

void motor_driver_stop(void)
{
    motorDriver.turnXRipples(0, false, false, 0); // stop motor
    motorMoving = false;
}

bool motor_driver_fault_active(void)
{
    return motorDriver.faultActive(); // relies on library's built-in fault check
}

bool motor_driver_is_active(void)
{
    return motorMoving;
}
