#!/bin/bash

SCRIPT_NAME=`basename $0`

function abort {
    echo "Usage: $SCRIPT_NAME file executable [pipe|socket]"
    echo -e "\tfile \t\topenocd configuration file (ex: board/st_nucleo_f0.cfg)"
    echo -e "\texecutable \tfile(elf, hex, ..)"
    echo -e "connection type pipe or socket"
    exit 1;
}


if [ $# -ne 3 ]; then
    abort
fi

OPENOCD_CFG=$1
FILENAME=$2


if [ -f $FILENAME ]; then
    if [ "$3" = "socket" ]; then
        xterm -T "openocd -f $OPENOCD_CFG" -e "openocd -f $OPENOCD_CFG" &
        OPENOCD_PID=$!
        arm-none-eabi-gdb -tui -x tools/gdb-socket.cfg $FILENAME
        kill $OPENOCD_PID
    elif [ "$3" = "pipe" ]; then
        arm-none-eabi-gdb -tui -x tools/gdb-pipe.cfg $FILENAME
    else
        abort
    fi
else
    abort
fi
