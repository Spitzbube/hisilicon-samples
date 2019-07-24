#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_animation \
    sample_bitmapfont \
    sample_dec \
    sample_effect \
    sample_encoder \
    sample_fillrect \
    sample_gdev \
    sample_logo \
    sample_performance \
    sample_surface \
    sample_wm

#SAMPLE_IMAGES += sample_scrolltext
SAMPLE_IMAGES += sample_stereo
SAMPLE_IMAGES += sample_text

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -lhi_common -lhi_msp -lhigo -lhigoadp -lfreetype -leffect -ldl -lstdc++

include $(SAMPLE_DIR)/hi_sample_rules.mak