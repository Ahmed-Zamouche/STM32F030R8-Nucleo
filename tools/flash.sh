#!/bin/bash

if [ $# -eq 0 ]; then
   exit 1
fi

FILENAME=$1
    
if [ -f $FILENAME ]; then
   openocd -f board/st_nucleo_f0.cfg -c "program $FILENAME verify reset exit"
else
	exit 2  
fi
