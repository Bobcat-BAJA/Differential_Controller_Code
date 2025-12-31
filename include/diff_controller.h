#ifndef DIFF_CONTROLLER_H
#define DIFF_CONTROLLER_H

#include <stdbool.h>
#include "diff_state_machine.h"

typedef enum {
    CTRL_INIT,
    CTRL_IDLE,
    CTRL_MOVING,
    CTRL_COOLDOWN,
    CTRL_RETRY_DELAY,
    CTRL_FAULT_LATCHED
} controller_state_t;

void diff_controller_init(void);
void diff_controller_update(void);
void diff_controller_request(diff_position_t requested);
bool diff_controller_is_busy(void);

#endif
