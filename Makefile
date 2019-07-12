
objects := log memdev userproc

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean $(objects)

all: $(objects)

clean:

install:

$(objects):
	$(AT)make -C $@
