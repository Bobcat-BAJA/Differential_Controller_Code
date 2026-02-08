#include "motor_driver.h"

static bool motorActive = false;

void motor_driver_init(void)
{
    pinMode(PIN_EN, OUTPUT);
    pinMode(PIN_PH, OUTPUT);
    pinMode(PIN_SLEEP, OUTPUT);
    pinMode(PIN_FAULT, INPUT_PULLUP);

    // Wake driver
    digitalWrite(PIN_SLEEP, HIGH);

    // Motor disabled initially
    digitalWrite(PIN_EN, LOW);
    digitalWrite(PIN_PH, LOW);

    motorActive = false;
}

void motor_driver_command(motor_command_t dir)
{
    if (dir == MOTOR_STOP) {
        motor_driver_stop();
        return;
    }

    // Direction
    digitalWrite(PIN_PH, (dir == MOTOR_FORWARD) ? HIGH : LOW);

    // Enable motor
    digitalWrite(PIN_EN, HIGH);
    motorActive = true;
}

void motor_driver_stop(void)
{
    digitalWrite(PIN_EN, LOW);
    motorActive = false;
}

bool motor_driver_fault_active(void)
{
    // DRV8214 FAULT is active LOW
    return digitalRead(PIN_FAULT) == LOW;
}

bool motor_driver_is_active(void)
{
    return motorActive;
}

