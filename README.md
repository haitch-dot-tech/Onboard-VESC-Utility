# Onboard VESC Utility
This code is a simple program that runs on an STM32F411 (WeAct BlackPill 3.0 here) and extracts serial data from a connected VESC. It then displays the data on a small TFT and shows the RPM on an LED strip.
It is mostly a proof of concept and will be completely different for the final product.

## Materials
- STM32F4 or BlackPill board
- 0.96" ST7735 Display
- VESC with Serial interface connected to USART1 on the STM32
- NeoPixel LED strip

## Hardware
Refer to `stm32pins`, `config.h`, or `User_Setup.h` (in `TFT_eSPI`) for where to connect everything.
Add your motor limits, wheel diameter, LED pixel count etc. in `config.h`.

## Code
Download the `.zip` file and extract it. Open the folder in VSCode (with PlatformIO) and build and upload it. If you don't have the STM32 platform already installed it may take a while.
