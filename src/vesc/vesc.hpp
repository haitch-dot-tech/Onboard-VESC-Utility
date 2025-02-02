/**
 * vesc.hpp
 * - Header for vesc.cpp
 */

#include <Arduino.h>
#include <VescUart.h>

#include "config.h"

struct motor_data
{
    bool gotValues;
    float VESCTemp;
    float motorTemp;
    float motorCurrent;
    float inputCurrent;
    float dutyCycle;
    float erpm;
    float rpm;
    float batteryVoltage;
    float ampHours;
    float ampHoursCharged;
    float wattHours;
    float wattHoursCharged;
    long tacho;
    long tachoAbs;
    uint8_t id;
};

void vesc_init();
motor_data vesc_data();
