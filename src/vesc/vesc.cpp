/**
 * vesc.cpp
 * - Wraps around the VescUart library
 */

#include "vesc.hpp"

VescUart vesc;

void vesc_init()
{
    Serial1.begin(115200);
    vesc.setSerialPort(&Serial1);
}

motor_data vesc_data()
{
    struct motor_data d = 
    {
        vesc.getVescValues(),
        vesc.data.tempFET,
        vesc.data.tempMotor,
        vesc.data.avgMotorCurrent,
        vesc.data.avgInputCurrent,
        vesc.data.dutyCycleNow,
        vesc.data.rpm,
        vesc.data.rpm / 7,
        vesc.data.inpVoltage,
        vesc.data.ampHours,
        vesc.data.ampHoursCharged,
        vesc.data.wattHours,
        vesc.data.wattHoursCharged,
        vesc.data.tachometer,
        vesc.data.tachometerAbs,
        vesc.data.id
    };
    return d;
}
