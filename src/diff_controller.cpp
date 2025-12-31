#include "diff_controller.h"
#include "diff_feedback.h"
#include <Arduino.h>
#include <can_arbitration_hw.h>

static controller_state_t state = CTRL_INIT;
static diff_position_t requestedPosition;
static unsigned long stateStartTime = 0;
static uint8_t retryCount = 0;

#define MAX_RETRIES 2
#define MOVE_TIMEOUT_MS 7000
#define RETRY_DELAY_MS 2000
#define COOLDOWN_TIME_MS 2000

void diff_controller_init(void)
{
    motor_driver_init();
    can_hw_init();
    diff_feedback_init();
    diff_state_machine_init();

    state = CTRL_IDLE;
}

void diff_controller_request(diff_position_t requested)
{
    if (!diff_controller_is_busy()) {
        requestedPosition = requested;
        diff_state_machine_request(requested);
        state = CTRL_MOVING;
        stateStartTime = millis();
    }
}

bool diff_controller_is_busy(void)
{
    return state != CTRL_IDLE;
}

void diff_controller_update(void)
{
    unsigned long now = millis();

    if (state == CTRL_MOVING) {
        diff_state_machine_update();
        if (!diff_state_machine_is_busy())
            state = CTRL_COOLDOWN;
        else if (now - stateStartTime > MOVE_TIMEOUT_MS)
            state = CTRL_FAULT_LATCHED;
    }

    if (state == CTRL_COOLDOWN && now - stateStartTime > COOLDOWN_TIME_MS)
        state = CTRL_IDLE;
}
