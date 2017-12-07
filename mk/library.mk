include mk/build.mk
#######################################
# paths
#######################################
# source path
SOURCES_DIR +=

# install path
INSTALL_DIR = install

######################################
# source
######################################
# C sources
C_SOURCES +=  \
Source/misc.c \
Source/console.c \
Source/button.c \
Source/led.c \
Source/pwm.c \
Source/timer.c \
Source/logger.c \

# ASM sources
ASM_SOURCES +=

#######################################
# CFLAGS
#######################################

# C defines
C_DEFS +=

# AS includes
AS_INCLUDES +=

# C includes
C_INCLUDES +=

#######################################
# build the library
#######################################
# list of objects
#LIB_OBJECTS:=$(subst main,lib_main,$(OBJECTS))

INSTALL_INCLUDE+=./include/*

library: all $(INSTALL_DIR)
	cp $(BUILD_DIR)/main.o $(BUILD_DIR)/lib_main.o
	$(AR)  rcs $(INSTALL_DIR)/lib/lib$(TARGET).a $(LIB_OBJECTS)
	mkdir -p $(INSTALL_DIR)/include
	cp -r $(INSTALL_INCLUDE)  $(INSTALL_DIR)/include
	cp $(LDSCRIPT) $(INSTALL_DIR)/lib/$(TARGET).ld
	$(shell echo -n ${BUILD_NUM} > ${BUILD_NUM_FILE})
$(INSTALL_DIR):
	mkdir -p $@/lib
