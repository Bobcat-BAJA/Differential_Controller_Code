#include <Arduino.h>
#include <FlexCAN_T4.h>
#include <cstring>
#include "can_arbitration_hw.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;

void can_hw_init(void)
{
    Can1.begin();
    Can1.setBaudRate(500000);
    Can1.enableFIFO();
}

bool can_hw_send(uint16_t can_id, uint8_t *data, uint8_t dlc)
{
    CAN_message_t frame;
    frame.id = can_id;
    frame.len = dlc;
    memcpy(frame.buf, data, dlc);
    return Can1.write(frame);
}

bool can_hw_receive(uint16_t *can_id, uint8_t *data, uint8_t *dlc)
{
    CAN_message_t frame;
    if (!Can1.read(frame)) return false;

    *can_id = frame.id;
    *dlc = frame.len;
    memcpy(data, frame.buf, frame.len);
    return true;
}
