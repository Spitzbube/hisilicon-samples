#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_blend \
    sample_colorfill \
    sample_colorkey \
    sample_deflicker \
    sample_quickcopy \
    sample_resize \
    sample_YUVtoRGB

LOCAL_OBJS  := tde_common.o

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -lhi_common -lhi_msp -ldl

include $(SAMPLE_DIR)/hi_sample_rules.mak