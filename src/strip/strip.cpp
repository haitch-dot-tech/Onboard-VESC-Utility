/**
 * strip.cpp
 * - Contains functions for running LED strip
 */

#include "strip.hpp"

RGB c;

Adafruit_NeoPixel strip(STRIP_NUM, STRIP_PIN, NEO_GRB + NEO_KHZ800);

void strip_init()
{
    strip.begin();
    strip.setPin(STRIP_PIN);
    strip.setBrightness(100);
}

void strip_setRPM(int rpm)
{
    if (rpm == -100000)
    {
        strip.setBrightness(25);
        strip.fill(strip.Color(255, 255, 255), 0, STRIP_NUM);
    }
    else
    {
        strip.setBrightness(100);
        for (int i = STRIP_NUM; i >= 0; i--)
        {
            if (i <= map(rpm, 0, MAX_RPM, 0, STRIP_NUM))
            {
                c = HSVtoRGB(map(i, 0, STRIP_NUM, MAX_HSV, 0), 1, 1);
                strip.setPixelColor(i, c.r, c.g, c.b);
            }
            else
            {
                strip.setPixelColor(i, 0, 0, 0);
            }
        }
    }
    strip.show();
}

RGB HSVtoRGB(float H, float S, float V)
{
    float C = V * S;
    float X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
    float m = V - C;

    float r, g, b;
    if (H >= 0 && H < 60)
    {
        r = C, g = X, b = 0;
    }
    else if (H < 120)
    {
        r = X, g = C, b = 0;
    }
    else if (H < 180)
    {
        r = 0, g = C, b = X;
    }
    else if (H < 240)
    {
        r = 0, g = X, b = C;
    }
    else if (H < 300)
    {
        r = X, g = 0, b = C;
    }
    else
    {
        r = C, g = 0, b = X;
    }

    return RGB{static_cast<int>((r + m) * 255),
               static_cast<int>((g + m) * 255),
               static_cast<int>((b + m) * 255)};
}
