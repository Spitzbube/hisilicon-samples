#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
#CFLAGS += -I$(MSP_DRV_INCLUDE)

SAMPLE_IMAGES := sample_audio_play

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -lhi_common -lhi_msp -ldl

include $(SAMPLE_DIR)/hi_sample_rules.mak
