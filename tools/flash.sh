#!/bin/bash

FILENAME=build/unittest/STM32F030R8-Nucleo.elf

openocd -f board/st_nucleo_f0.cfg -c "program $FILENAME verify reset exit"
