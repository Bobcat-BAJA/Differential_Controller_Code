#ifndef DIFF_STATE_MACHINE_H
#define DIFF_STATE_MACHINE_H

#include <stdbool.h>
#include "motor_driver.h"

typedef enum {
    DIFF_OPEN = 0,
    DIFF_SEMI,
    DIFF_LOCKED,
    DIFF_INVALID
} diff_position_t;

void diff_state_machine_init(void);
void diff_state_machine_update(void);
void diff_state_machine_request(diff_position_t requested);
bool diff_state_machine_is_busy(void);

#endif

