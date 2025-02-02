/**
 * main.cpp
 * - Main file for code
 */

#include <Arduino.h>
#include "ui/ui.hpp"
#include "strip/strip.hpp"
#include "vesc/vesc.hpp"

#include "config.h"

int lastMillis = 0;
int currentScreen = 1;

motor_data m;
update_data u;

void setup()
{
    ui_hardware_init();
    ui_init();
    ui_load_screen(currentScreen);

    strip_init();
    strip_setRPM(-1);

    vesc_init();

    pinMode(KEY, INPUT_PULLUP);
}

void loop()
{
    if (digitalRead(KEY) == LOW)
    {
        if (millis() - lastMillis > 250)
        {
            currentScreen++;
            if (currentScreen == 8)
                currentScreen = 1;
            lastMillis = millis();
            ui_load_screen(currentScreen);
        }
    }

    m = vesc_data();

    strip_setRPM((m.gotValues) ? m.rpm : -100000);

    u.connected = m.gotValues;
    u.id = m.id;
    u.voltage = m.batteryVoltage;
    u.rpm = m.rpm;
    u.speed = PI * (WHEEL_DIA / 1000.0) * m.rpm * (18.0 / 200.0) / 60.0 * 3.6;
    u.tempFET = m.VESCTemp;
    u.tempMTR = m.motorTemp;
    u.duty = m.dutyCycle;
    u.tacho = m.tacho;
    u.ampHours = m.ampHours;
    u.ampHoursCharged = m.ampHoursCharged;
    u.wattHours = m.wattHours;
    u.wattHoursCharged = m.wattHoursCharged;

    ui_update(u);
}
