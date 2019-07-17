
objects := log memdev userproc \
           fb tde

objects += hdmi

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

