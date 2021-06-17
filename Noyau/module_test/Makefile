ifneq ($(KERNELRELEASE),)
obj-m := module_test.o
else
KDIR := /usr/src/linux-headers-5.8.0-55-generic/

all:
	$(MAKE) -C $(KDIR) M=$$PWD

.PHONY : clean
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

endif
