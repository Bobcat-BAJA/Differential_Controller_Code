#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <stdint.h>

// Dash / HID
#define CAN_ID_DASH          0x06
#define CAN_ID_DASH_HID      0x07

// Differential controllers (repurposed GPIO IDs)
#define CAN_ID_FRONT_DIFF    0x08
#define CAN_ID_REAR_DIFF     0x09

typedef enum {
    DIFF_CAN_OPEN   = 0x00,
    DIFF_CAN_SEMI   = 0x01,
    DIFF_CAN_LOCKED = 0x02,
    DIFF_CAN_UNDEF  = 0xFF
} diff_can_state_t;

#endif
