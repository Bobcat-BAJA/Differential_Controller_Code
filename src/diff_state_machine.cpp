#include "diff_state_machine.h"
#include <Arduino.h>

// ---------- State machine variables ----------
static diff_position_t currentPosition = DIFF_INVALID;
static diff_position_t targetPosition  = DIFF_INVALID;
static bool busy = false;
static uint8_t retryCount = 0;
static unsigned long moveStartTime = 0;
static unsigned long lastRetryTime = 0;

// Example LED function (replace with your actual LED logic)
void setDiffLED(diff_position_t pos)
{
    switch (pos)
    {
        case DIFF_OPEN:    /* GREEN */ break;
        case DIFF_SEMI:    /* BLUE */  break;
        case DIFF_LOCKED:  /* RED */   break;
        case DIFF_INVALID: /* BLINK ERROR */ break;
    }
}

// ---------- Initialization ----------
void diff_state_machine_init(void)
{
    currentPosition = DIFF_OPEN; // assume default
    targetPosition  = DIFF_OPEN;
    busy = false;
    retryCount = 0;
    moveStartTime = 0;
    lastRetryTime = 0;
}

// ---------- Request a new position ----------
void diff_state_machine_request(diff_position_t requested)
{
    // Ignore requests while busy
    if (busy) return;

    // Only update if different
    if (requested != currentPosition)
    {
        targetPosition = requested;
        busy = true;
        moveStartTime = millis();
        retryCount = 0;
    }
}

// ---------- Returns true if motor is moving ----------
bool diff_state_machine_is_busy(void)
{
    return busy;
}

// ---------- Main update function ----------
void diff_state_machine_update(void)
{
    if (!busy) return;

    // Check if move has timed out
    if (millis() - moveStartTime > 7000) // MAX_MOVE_TIME_MS
    {
        motor_driver_stop();
        busy = false;
        currentPosition = DIFF_INVALID;
        retryCount++;
        lastRetryTime = millis();
        return;
    }

    // Determine motor direction based on current vs target
    motor_command_t dir = MOTOR_STOP;
    if (currentPosition == DIFF_OPEN && targetPosition == DIFF_SEMI)
        dir = MOTOR_FORWARD;
    else if (currentPosition == DIFF_OPEN && targetPosition == DIFF_LOCKED)
        dir = MOTOR_FORWARD;
    else if (currentPosition == DIFF_SEMI && targetPosition == DIFF_OPEN)
        dir = MOTOR_REVERSE;
    else if (currentPosition == DIFF_SEMI && targetPosition == DIFF_LOCKED)
        dir = MOTOR_FORWARD;
    else if (currentPosition == DIFF_LOCKED && targetPosition == DIFF_SEMI)
        dir = MOTOR_REVERSE;
    else if (currentPosition == DIFF_LOCKED && targetPosition == DIFF_OPEN)
        dir = MOTOR_REVERSE;

    motor_driver_command(dir);

    // TODO: Replace this with actual position read from hardware pins
    // Here we simulate it reaching the target after 2 seconds
    if (millis() - moveStartTime > 2000)
    {
        motor_driver_stop();
        currentPosition = targetPosition;
        busy = false;
        retryCount = 0;
    }

    // Update LEDs
    setDiffLED(currentPosition);
}
