#include <Arduino.h>
#include <FlexCAN_T4.h>
#include "can_arbitration_hw.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;

void can_hw_init()
{
    Can1.begin();
    Can1.setBaudRate(500000);
    Can1.enableFIFO();
}

bool can_hw_send(uint8_t sender, uint8_t command, uint8_t signature)
{
    CAN_message_t frame;
    frame.id = sender;
    frame.len = 2;
    frame.buf[0] = command;
    frame.buf[1] = signature;
    return Can1.write(frame);
}

bool can_hw_receive(uint8_t *sender, uint8_t *command, uint8_t *signature)
{
    CAN_message_t frame;
    if (!Can1.read(frame)) return false;

    *sender = frame.id & 0xFF;
    *command = frame.buf[0];
    *signature = frame.buf[1];
    return true;
}
