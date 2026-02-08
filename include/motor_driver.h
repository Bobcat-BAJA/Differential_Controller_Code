#pragma once
#include <Arduino.h>
#include <stdbool.h>

typedef enum {
    MOTOR_STOP = 0,
    MOTOR_FORWARD,
    MOTOR_REVERSE
} motor_command_t;

// ===== DRV8214 ↔ Teensy 4.0 pin mapping =====
constexpr uint8_t PIN_IPROPI = 21;
constexpr uint8_t PIN_SLEEP  = 20;
constexpr uint8_t PIN_SDA    = 19; // not used yet
constexpr uint8_t PIN_SCL    = 18; // not used yet
constexpr uint8_t PIN_FAULT  = 17;
constexpr uint8_t PIN_RCOUT  = 16;
constexpr uint8_t PIN_EN     = 15;
constexpr uint8_t PIN_PH     = 14;

// ===== API (used by state machine) =====
void motor_driver_init(void);
void motor_driver_command(motor_command_t dir);
void motor_driver_stop(void);
bool motor_driver_fault_active(void);
bool motor_driver_is_active(void);
