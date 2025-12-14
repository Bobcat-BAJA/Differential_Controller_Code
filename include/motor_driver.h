#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_STOP = 0,
    MOTOR_FORWARD,
    MOTOR_REVERSE
} motor_command_t;

/* Commands the motor in a given direction */
void motor_driver_command(motor_command_t dir);

/* Stops the motor */
void motor_driver_stop(void);

/* Returns true if the motor reports a fault */
bool motor_driver_fault_active(void);

/* Returns true if the motor is currently moving */
bool motor_driver_is_active(void);

/* Initialize the motor driver (call in setup) */
void motor_driver_init(void);

#endif
