#include "diff_state_machine.h"
#include "diff_feedback.h"
#include <Arduino.h>

static diff_position_t currentPosition;
static diff_position_t targetPosition;
static bool busy = false;
static unsigned long moveStartTime = 0;

void diff_state_machine_init(void)
{
    currentPosition = get_top_diff_state();
    targetPosition = currentPosition;
    busy = false;
}

void diff_state_machine_request(diff_position_t requested)
{
    if (busy) return;
    if (requested != currentPosition) {
        targetPosition = requested;
        busy = true;
        moveStartTime = millis();
    }
}

bool diff_state_machine_is_busy(void)
{
    return busy;
}

void diff_state_machine_update(void)
{
    if (!busy) return;

    if (millis() - moveStartTime > 7000) {
        motor_driver_stop();
        currentPosition = DIFF_INVALID;
        busy = false;
        return;
    }

    diff_position_t actual = get_top_diff_state();

    if (actual == targetPosition) {
        motor_driver_stop();
        currentPosition = actual;
        busy = false;
        return;
    }

    motor_command_t dir =
        (actual < targetPosition) ? MOTOR_FORWARD : MOTOR_REVERSE;

    motor_driver_command(dir);
}
