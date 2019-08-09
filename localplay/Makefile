#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================

CFLAGS += -DCHARSET_SUPPORT

SAMPLE_IMAGES := sample_localplay

LOCAL_OBJS := play_m3u9.o 

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -lhi_common -lhi_msp -lhigo -lhigoadp -lfreetype -lhi_so -ldl -lstdc++
DEPEND_LIBS += -lhi_charsetMgr -lsubdec -lplayer -lhiplayer_utils

include $(SAMPLE_DIR)/hi_sample_rules.mak
