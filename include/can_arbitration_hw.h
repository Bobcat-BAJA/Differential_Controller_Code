#ifndef CAN_ARBITRATION_HW_H
#define CAN_ARBITRATION_HW_H

#include <stdint.h>
#include <stdbool.h>

/* Initialize CAN hardware */
void can_hw_init(void);

/* Send a command with a signature over CAN */
void can_hw_send(uint8_t signature, uint8_t command);

/* Receive a CAN message. Returns true if a message was received */
bool can_hw_receive(uint8_t *signature, uint8_t *command, uint8_t *sender);

#endif
