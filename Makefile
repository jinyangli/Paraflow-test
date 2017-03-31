CC=gcc

MKLROOT=/opt/intel/mkl
INTEL_OPENMPROOT=/opt/intel/compilers_and_libraries/linux/

INCLUDES=-std=gnu99 -static -DMKL_ILP64 -m64 -I$(MKLROOT)/include
LINKS=-Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_ilp64.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -L$(INTEL_OPENMPROOT)/lib/intel64 -liomp5 -lpthread -lm -ldl

all : blastest mkltest 

blastest: blastest.c
	$(CC) $^ -o blastest -lrt -lgslcblas

mkltest: mkltest.c	
	 $(CC) $(INCLUDES) $^ -o mkltest $(LINKS) 

clean:
	rm -rf blastest mkltest
