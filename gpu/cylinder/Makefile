#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS  :=  -I$(SAMPLE_DIR)/gpu/common/inc \
            -I$(SAMPLE_DIR)/gpu/common/egl/inc \
            -I$(SAMPLE_DIR)/gpu/common/key/inc \
            -I$(SAMPLE_DIR)/gpu/common/texture/inc

CFLAGS += -DHI3D_DEBUG -DLINUX -DEGL_API_FB 
CFLAGS += -DEGL_FBDEV

DEPEND_LIBS := -lhi_common -lhi_msp -lhigo -lhigoadp -lfreetype
DEPEND_LIBS += -lmali -lstdc++ -lm
DEPEND_LIBS += -lEGL -lGLESv1_CM

GPU_COMMON_OBJS :=  ../common/egl/src/hi_egl.o \
                    ../common/egl/src/egl_native.o

SAMPLE_IMAGES := sample_cylinder

LOCAL_OBJS := cylinder_menu.o cylinder_texture.o hi_cylinder.o $(GPU_COMMON_OBJS)

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

include $(SAMPLE_DIR)/hi_sample_rules.mak
