all : blastest mkltest 

blastest: blastest.c
	gcc $^ -o blastest -lrt -lgslcblas

mkltest: mkltest.c	
	 gcc -m64 -static $^ -o mkltest -I/opt/intel/mkl/include -Wl,--start-group -L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_core  -lmkl_intel_thread -Wl,--end-group -L/opt/intel/compilers_and_libraries/linux/lib/intel64 -liomp5 -ldl -lm -lpthread
