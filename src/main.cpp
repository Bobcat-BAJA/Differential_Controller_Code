#include <Arduino.h>
#include "diff_controller.h"

/*
 * Differential Controller – Main Entry Point
 *
 * This file is intentionally minimal.
 * It only:
 *  - Initializes the controller once
 *  - Continuously updates the controller
 *
 * All logic lives in the controller, state machine, and CAN layers.
 */

void setup(void)
{
    Serial.begin(115200);

    // Initialize the entire differential controller stack
    diff_controller_init();

    Serial.println("Differential Controller Online");
}

void loop(void)
{
    // Run controller logic (non-blocking)
    diff_controller_update();
}
