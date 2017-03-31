CC=gcc

CFLAGS=-std=gnu99 
MKLROOT=/opt/intel/mkl
INTEL_OPENMPROOT=/opt/intel/compilers_and_libraries/linux/

MKL_INCLUDE=-static -DMKL_ILP64 -m64 -I$(MKLROOT)/include
MKL_LINKS=-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -L$(INTEL_OPENMPROOT)/lib/intel64 -liomp5 -lpthread -lm -ldl

all : blastest mkltest 

blastest: blastest.c
	$(CC) $(CFLAGS) $^ -o blastest -lrt -lgslcblas

mkltest: mkltest.c	
	 $(CC) $(CFLAGS) $(MKL_INCLUDE) $^ -o mkltest $(MKL_LINKS) 

clean:
	rm -rf blastest mkltest
