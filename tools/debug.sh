#!/bin/bash

if [ $# -eq 0 ]; then  
   exit 1
fi

FILENAME=$1

if [ -f $FILENAME ]; then
	if [ "$2" = "socket" ]; then
	    xterm -T "openocd -f board/stm32f4discovery.cfg" -e "openocd -f board/stm32f4discovery.cfg" &
	    OPENOCD_PID=$!
	    arm-none-eabi-gdb -tui -x tools/gdb-socket.cfg $FILENAME
	    kill $OPENOCD_PID
	elif [ "$2" = "pipe" ]; then
	    arm-none-eabi-gdb -tui -x tools/gdb-pipe.cfg $FILENAME
	else
		exit 3
	fi
else
	exit 2	
fi
