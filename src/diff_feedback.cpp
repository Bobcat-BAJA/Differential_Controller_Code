#include "diff_feedback.h"

void diff_feedback_init(void)
{
    pinMode(DIF1_PIN, INPUT);
    pinMode(DIF3_PIN, INPUT);
    pinMode(DIF4_PIN, INPUT);
}

diff_position_t get_top_diff_state(void)
{
    bool d1 = digitalRead(DIF1_PIN);
    bool d3 = digitalRead(DIF3_PIN);
    bool d4 = digitalRead(DIF4_PIN);

    if (d4 && !d3 && !d1) return DIFF_OPEN;
    if (d4 && d3 && !d1)  return DIFF_SEMI;
    if (!d4 && d3 && d1)  return DIFF_LOCKED;

    return DIFF_INVALID;
}
