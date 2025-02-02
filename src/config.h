/**
 * config.h
 * - Holds hardware config for setup
 */

#pragma once

/* Built in Peripherals */
#define KEY PA0
#define LED PC13

/* LED Strip Setup */
#define STRIP_NUM 72
#define STRIP_PIN PB5
#define MAX_HSV 64

/* Display config */
#define HEIGHT 80
#define WIDTH 160
#define SCREEN_LOAD_DELEAY 250

/* Motor setup */
#define MAX_RPM 8400
#define WHEEL_DIA 430.0 // mm 
