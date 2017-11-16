BUILD_NUM_FILE:=mk/build.num

ifeq ($(wildcard  ${BUILD_NUM_FILE}),) 
 $(shell echo -n 0 > ${BUILD_NUM_FILE})
 BUILD_NUM:=0
else
 BUILD_NUM_PRV:=$(shell cat ${BUILD_NUM_FILE})
 BUILD_NUM:=$(shell echo -n $$(( ${BUILD_NUM_PRV} + 1 )))
endif
BUILD_DATE:=$(shell date +%s)

# C defines
C_DEFS +=-DBUILD_NUM=$(BUILD_NUM) -DBUILD_DATE=$(BUILD_DATE)
