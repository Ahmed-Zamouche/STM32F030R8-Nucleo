#!/bin/bash

FILENAME=build/unittest/STM32F030R8-Nucleo.elf

if [ $1 = "socket" ]
then
    xterm -T "openocd -f board/st_nucleo_f0.cfg" -e "openocd -f board/st_nucleo_f0.cfg" &
    OPENOCD_PID=$!
    arm-none-eabi-gdb -tui -x tools/gdb-socket.cfg $FILENAME
    kill $OPENOCD_PID
else
    arm-none-eabi-gdb -tui -x tools/gdb-pipe.cfg $FILENAME
fi
