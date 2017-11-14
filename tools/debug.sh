#!/bin/bash

arm-none-eabi-gdb -tui -x tools/debug.txt build/unittest/STM32F030R8-Nucleo.elf
