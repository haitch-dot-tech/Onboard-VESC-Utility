/**
 * ui.hpp
 * - Header for ui.cpp
 */

#include <Arduino.h>
#include "lvgl.h"
#include <TFT_eSPI.h>

#include "config.h"

struct update_data
{
    bool connected;
    uint8_t id;
    float voltage;
    int rpm;
    float speed;
    float tempFET;
    float tempMTR;
    float duty;
    long tacho;
    float ampHours;
    float ampHoursCharged;
    float wattHours;
    float wattHoursCharged;
};

static uint32_t lv_tick(void);

void ui_hardware_init();
void ui_init();
void ui_load_screen(int scr);
void ui_update();
void ui_update(struct update_data d);
