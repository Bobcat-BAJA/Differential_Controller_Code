#include <Arduino.h>
#include "diff_controller.h"
#include "motor_driver.h"
#include "can_arbitration_hw.h"

// Simulated switch positions (replace with real pins later)
#define SWITCH_OPEN   0
#define SWITCH_SEMI   1
#define SWITCH_LOCKED 2

uint8_t simulatedSwitch = SWITCH_OPEN;

void setup() {
    Serial.begin(115200);
    motor_driver_init();
    can_hw_init();
    diff_state_machine_init();
    diff_controller_init();

    Serial.println("Diff controller initialized");
}

void loop() {
    // 1️⃣ Update the controller every loop
    diff_controller_update();

    // 2️⃣ Example: change simulated switch every 5 seconds
    static unsigned long lastSwitchTime = 0;
    if (millis() - lastSwitchTime > 5000) {
        lastSwitchTime = millis();

        // Rotate through switch states
        simulatedSwitch = (simulatedSwitch + 1) % 3;

        // Request move based on simulated switch
        switch(simulatedSwitch) {
            case SWITCH_OPEN:
                diff_controller_request(DIFF_OPEN);
                Serial.println("Requesting OPEN");
                break;
            case SWITCH_SEMI:
                diff_controller_request(DIFF_SEMI);
                Serial.println("Requesting SEMI");
                break;
            case SWITCH_LOCKED:
                diff_controller_request(DIFF_LOCKED);
                Serial.println("Requesting LOCKED");
                break;
        }
    }

    delay(10); // small delay for stability
}
