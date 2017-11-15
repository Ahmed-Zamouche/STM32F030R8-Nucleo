#!/bin/bash

arm-none-eabi-gdb  -x tools/flash.txt build/unittest/STM32F030R8-Nucleo.elf
#arm-none-eabi-gdb  -x tools/flash.txt build/STM32F030R8-Nucleo.elf
