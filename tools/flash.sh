#!/bin/bash

if [ $# -eq 0 ]; then
   exit 1
fi

FILENAME=$1
    
if [ -f $FILENAME ]; then
   openocd -f board/stm32f4discovery.cfg -c "program $FILENAME verify reset exit"
else
	exit 2  
fi
