#===============================================================================
# export variable
#===============================================================================

#include $(SDK_DIR)/base.mak

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C play all
	$(AT)make -C mix all
	$(AT)make -C mp3_spectrum all

clean:
	$(AT)make -C play clean
	$(AT)make -C mix clean
	$(AT)make -C mp3_spectrum clean

install:
	$(AT)make -C play install
	$(AT)make -C mix install
	$(AT)make -C mp3_spectrum install

uninstall:
	$(AT)make -C play uninstall
	$(AT)make -C mix uninstall
	$(AT)make -C mp3_spectrum uninstall
