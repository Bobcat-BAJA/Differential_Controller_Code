#ifndef DIFF_FEEDBACK_H
#define DIFF_FEEDBACK_H

#include <Arduino.h>
#include "diff_state_machine.h"

// Worm-gear feedback pins
// MP3 = pin 8
// MP2 = pin 9
// MP1 = pin 10
#define DIF4_PIN  8   // MP3
#define DIF3_PIN  9   // MP2
#define DIF1_PIN  10  // MP1

void diff_feedback_init(void);
diff_position_t get_top_diff_state(void);

#endif
