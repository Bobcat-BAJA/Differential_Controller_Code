#include "motor_driver.h"
#include "DRV8214.h"
#include <Wire.h>

DRV8214 motorDriver(0x60, 0, 3600, 156, 0, 1, 3000);
DRV8214_Config cfg;
static bool motorMoving = false;

void motor_driver_init(void)
{
    Wire.begin();
    motorDriver.init(cfg);
}

void motor_driver_command(motor_command_t dir)
{
    if (dir == MOTOR_FORWARD)
        motorDriver.turnXRipples(50000, true, true, 1);
    else if (dir == MOTOR_REVERSE)
        motorDriver.turnXRipples(50000, false, true, 1);
    else
        motor_driver_stop();

    motorMoving = (dir != MOTOR_STOP);
}

void motor_driver_stop(void)
{
    motorDriver.turnXRipples(0, false, false, 0);
    motorMoving = false;
}

bool motor_driver_fault_active(void)
{
    return false;
}

bool motor_driver_is_active(void)
{
    return motorMoving;
}
