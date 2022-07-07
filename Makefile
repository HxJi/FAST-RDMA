KSRC=/lib/modules/`uname -r`/build
KOBJ=/lib/modules/`uname -r`/build

KBUILD_EXTRA_SYMBOLS += /lib/modules/$(shell uname -r)/build/Module.symvers
export KBUILD_EXTRA_SYMBOLS
ccflags-y := -Wunused -O0 -mpreferred-stack-boundary=4 -mavx2 #-ftree-vectorize

obj-m += rdma_krping.o
rdma_krping-y			:= getopt.o krping.o

default:
	make -C $(KSRC) M=`pwd` modules

install:
	make -C $(KSRC) M=`pwd` modules_install
	depmod -a

clean:
	rm -f *.o
	rm -f *.ko
	rm -f rdma_krping.mod.c
	rm -f Module.symvers
	rm -f Module.markers
