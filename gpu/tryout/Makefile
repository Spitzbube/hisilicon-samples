#===============================================================================
# export variable
#===============================================================================

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================

CFLAGS := -I$(SAMPLE_DIR)/gpu/common/inc \
          -I$(SAMPLE_DIR)/gpu/common/egl/inc

CFLAGS += -DHI3D_DEBUG -DLINUX -DEGL_API_FB 
CFLAGS += -DEGL_FBDEV
            
DEPEND_LIBS := -lhi_common -lhi_msp
DEPEND_LIBS += -lmali -lstdc++
DEPEND_LIBS += -lEGL -lGLESv1_CM

#GPU_COMMON_OBJS :=  ../common/egl/src/hi_egl.o \
                    ../common/egl/src/egl_native.o \
                    ../common/texture/src/hi_texture.o \
                    ../common/key/src/hi_engine_key.o \
                    ../common/key/src/hi_input_dfb.o \
                    ../common/key/src/hi_ir_remote.o

SAMPLE_IMAGES := sample_gpu

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

include $(SAMPLE_DIR)/hi_sample_rules.mak
