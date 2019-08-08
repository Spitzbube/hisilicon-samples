#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_tsplay \
    sample_tsplay_pid \
    sample_tsplay_multiaud \

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -lhi_common -lhi_msp -ldl

include $(SAMPLE_DIR)/hi_sample_rules.mak
