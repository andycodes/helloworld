
CFLAGS += -Isrc/cmsis \
			-Isrc/cmsis/CMSIS/Core/Include \
			-Isrc/cmsis/CMSIS/DSP/Include \
		    -Isrc/cmsis/CMSIS/DSP/Include/dsp/


CSRC +=	src/cmsis/CMSIS/DSP/Source/BasicMathFunctions/arm_clip_q7.c