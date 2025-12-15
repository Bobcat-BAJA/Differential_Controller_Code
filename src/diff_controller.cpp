#include "diff_controller.h"
#include "motor_driver.h"
#include "can_arbitration_hw.h"
#include <Arduino.h>

// ---------- Controller variables ----------
static controller_state_t state = CTRL_INIT;
static diff_position_t requestedPosition = DIFF_OPEN;
static unsigned long stateStartTime = 0;
static uint8_t retryCount = 0;

#define MAX_RETRIES 2
#define MOVE_TIMEOUT_MS 7000
#define RETRY_DELAY_MS 2000
#define COOLDOWN_TIME_MS 2000

// ---------- Initialize the controller ----------
void diff_controller_init(void)
{
    motor_driver_init();
    can_hw_init();
    diff_state_machine_init();
    state = CTRL_IDLE;
    retryCount = 0;
    stateStartTime = millis();
}

// ---------- Request a move ----------
void diff_controller_request(diff_position_t requested)
{
    if (!diff_controller_is_busy())
    {
        requestedPosition = requested;
        state = CTRL_MOVING;
        stateStartTime = millis();
        diff_state_machine_request(requestedPosition);
    }
}

// ---------- Returns true if controller is busy ----------
bool diff_controller_is_busy(void)
{
    return state == CTRL_MOVING || state == CTRL_RETRY_DELAY || state == CTRL_COOLDOWN;
}

// ---------- Main controller update function ----------
void diff_controller_update(void)
{
    unsigned long now = millis();

    switch(state)
    {
        case CTRL_INIT:
            state = CTRL_IDLE;
            break;

        case CTRL_IDLE:
            // Idle: check for new requests
            break;

        case CTRL_MOVING:
            diff_state_machine_update();

            if (!diff_state_machine_is_busy())
            {
                // Move complete
                state = CTRL_COOLDOWN;
                stateStartTime = now;
            }
            else if (now - stateStartTime > MOVE_TIMEOUT_MS)
            {
                // Move timeout: stop and retry
                motor_driver_stop();
                retryCount++;
                state = (retryCount > MAX_RETRIES) ? CTRL_FAULT_LATCHED : CTRL_RETRY_DELAY;
                stateStartTime = now;
            }
            break;

        case CTRL_RETRY_DELAY:
            // Wait before retrying
            if (now - stateStartTime >= RETRY_DELAY_MS)
            {
                diff_state_machine_request(requestedPosition);
                state = CTRL_MOVING;
                stateStartTime = now;
            }
            break;

        case CTRL_COOLDOWN:
            if (now - stateStartTime >= COOLDOWN_TIME_MS)
            {
                state = CTRL_IDLE;
                retryCount = 0;
            }
            break;

        case CTRL_FAULT_LATCHED:
            motor_driver_stop();
            // TODO: Add LED indication for latched fault
            break;
    }
}
