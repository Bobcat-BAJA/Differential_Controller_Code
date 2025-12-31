#ifndef CAN_ARBITRATION_HW_H
#define CAN_ARBITRATION_HW_H

#include <stdint.h>
#include <stdbool.h>

void can_hw_init(void);
bool can_hw_send(uint16_t can_id, uint8_t *data, uint8_t dlc);
bool can_hw_receive(uint16_t *can_id, uint8_t *data, uint8_t *dlc);

#endif
