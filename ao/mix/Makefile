#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_mixengine

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SAMPLE_IMAGES += sample_audio_mix
endif

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -lhi_common -lhi_msp -ldl

include $(SAMPLE_DIR)/hi_sample_rules.mak
