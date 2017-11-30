
INSTALL_INCLUDE+=./lib/dsp/fft/include/fft.h

ifeq ($(FFT_IMPL_F32), 1)
 INSTALL_INCLUDE+=./lib/dsp/fft/include/fft_f32.h
 C_DEFS+=-DFFT_IMPL_F32
else ifeq ($(FFT_IMPL_Q8_7), 1)
 INSTALL_INCLUDE+=./lib/dsp/fft/include/fft_q8_7.h
 C_DEFS+=-DFFT_IMPL_Q8_7
endif


C_INCLUDES+=-I./lib/dsp/fft/include

C_SOURCES+=./lib/dsp/fft/src/fft.c

