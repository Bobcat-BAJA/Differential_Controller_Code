#ifndef DIFF_FEEDBACK_H
#define DIFF_FEEDBACK_H

#include <Arduino.h>
#include "diff_state_machine.h"

// Worm-gear feedback pins
#define DIF1_PIN  2
#define DIF3_PIN  3
#define DIF4_PIN  4

void diff_feedback_init(void);
diff_position_t get_top_diff_state(void);

#endif
