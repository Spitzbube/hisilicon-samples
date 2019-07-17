#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
ifeq ($(CFG_HI_FB_DECOMPRESS_SUPPORT),y)
CFLAGS := -DHI_FB_DECOMPRESS_SUPPORT
endif

SAMPLE_IMAGES := sample_fb sample_decmp_fb

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -lhi_common -lhi_msp

include $(SAMPLE_DIR)/hi_sample_rules.mak
