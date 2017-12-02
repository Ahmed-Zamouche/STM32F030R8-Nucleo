#!/bin/bash


SCRIPT_NAME=`basename $0`;

function abort {
    echo "Usage: $SCRIPT_NAME file executable"
    echo -e "\tfile \t\topenocd configuration file (ex: board/st_nucleo_f0.cfg)"
    echo -e "\texecutable \tfile(elf, hex, ..)"
    exit 1;
}


if [ $# -ne 2 ]; then
   abort
fi

OPENOCD_CFG=$1
FILENAME=$2

if [ -f $FILENAME ]; then
   openocd -f $OPENOCD_CFG -c "program $FILENAME verify reset exit"
else
    abort
fi
