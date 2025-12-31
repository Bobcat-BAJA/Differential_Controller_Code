#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdbool.h>

typedef enum {
    MOTOR_STOP = 0,
    MOTOR_FORWARD,
    MOTOR_REVERSE
} motor_command_t;

void motor_driver_init(void);
void motor_driver_command(motor_command_t dir);
void motor_driver_stop(void);
bool motor_driver_fault_active(void);
bool motor_driver_is_active(void);

#endif
