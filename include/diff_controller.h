#ifndef DIFF_CONTROLLER_H
#define DIFF_CONTROLLER_H

#include <stdint.h>
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

/* Initialize the differential controller */
void diff_controller_init(void);

/* Update controller state (call every loop) */
void diff_controller_update(void);

/* Request a new differential position */
void diff_controller_request(diff_position_t requested);

/* Returns true if motor or controller is busy */
bool diff_controller_is_busy(void);

#endif
