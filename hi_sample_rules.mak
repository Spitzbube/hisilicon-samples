
OBJ_DIR := $(SAMPLE_DIR)/obj
COMMON_OBJ_DIR := $(SAMPLE_DIR)/obj

HI_SAMPLE_IMAGES := $(addprefix $(OBJ_DIR)/,$(SAMPLE_IMAGES))
HI_COMMON_OBJS := $(addprefix $(COMMON_OBJ_DIR)/,$(COMMON_OBJS)) 

CFLAGS  += $(CFG_HI_SAMPLE_CFLAGS)
CFLAGS  += -I$(SAMPLE_DIR)/common

HI_DEPEND_LIBS := -Wl,--start-group $(SYS_LIBS) $(DEPEND_LIBS) -Wl,--end-group

TARGETS :=

TARGETS += $(if $(HI_SAMPLE_IMAGES),$(HI_SAMPLE_IMAGES),$(HI_COMMON_OBJS))


#===============================================================================
# rules
#===============================================================================

all: $(TARGETS)

$(HI_SAMPLE_IMAGES) : % : $(HI_COMMON_OBJS) $(addprefix $(OBJ_DIR)/,$(LOCAL_OBJS)) %.o
	$(CC) -o $@ $^ $(HI_DEPEND_LIBS)

$(OBJ_DIR)/%.o : %.c
	$(AT)test -d $(dir $@) || mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $^


