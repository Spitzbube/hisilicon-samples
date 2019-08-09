#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_mp3_spectrum

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -lhi_common -lhi_msp -ldl -lstdc++
DEPEND_LIBS += -lhigo -lhigoadp -lfreetype

include $(SAMPLE_DIR)/hi_sample_rules.mak
