#!/bin/bash

make -j 4 && make -j 4 library && make -j 4 -f mk/unittest.mk
