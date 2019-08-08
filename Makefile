
objects := esplay tsplay log memdev userproc \
           fb higo tde

objects += hdmi

objects += gpu

objects += rawplay

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean $(objects)

all: $(objects)

clean:

install:

$(objects): sample_common
	$(AT)make -C $@

sample_common:
	$(AT)make -C common

