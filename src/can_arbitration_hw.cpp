#include "can_arbitration_hw.h"
#include <FlexCAN_T4.h>
#include <Arduino.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CANbus;
CAN_message_t frame;
#define CAN_ARB_ID 0x51  // CAN ID for diff control messages

void can_hw_init(void)
{
    CANbus.begin();
    CANbus.setBaudRate(500000);
    CANbus.enableFIFO();
}

void can_hw_send(uint8_t signature, uint8_t command)
{
    frame.id  = CAN_ARB_ID;
    frame.len = 2;
    frame.buf[0] = signature;
    frame.buf[1] = command;
    CANbus.write(frame);
}

bool can_hw_receive(uint8_t *signature, uint8_t *command, uint8_t *sender)
{
    if (CANbus.read(frame))
    {
        if (frame.id != CAN_ARB_ID) return false;
        *signature = frame.buf[0];
        *command   = frame.buf[1];
        *sender    = frame.ext ? 1 : 0;
        return true;
    }
    return false;
}
