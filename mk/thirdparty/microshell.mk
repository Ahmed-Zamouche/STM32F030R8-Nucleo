
MICROSHELL_PATH := ./thirdparty/microshell/src/lib

INSTALL_INCLUDE+=$(wildcard $(MICROSHELL_PATH)/core/*.h) \
$(wildcard $(MICROSHELL_PATH)/util/*.h) \


C_INCLUDES+=-I$(MICROSHELL_PATH)/core/ \
-I$(MICROSHELL_PATH)/util/

C_SOURCES+=$(wildcard $(MICROSHELL_PATH)/core/*.c) \
$(wildcard $(MICROSHELL_PATH)/util/*.c) \

