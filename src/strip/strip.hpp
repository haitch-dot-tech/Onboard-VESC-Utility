/**
 * strip.hpp
 * - Header for strip.cpp
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <iostream>
#include <cmath>

#include "config.h"

struct RGB
{
    int r, g, b;
};

void strip_init();
void strip_setRPM(int rpm);

RGB HSVtoRGB(float H, float S, float V);
