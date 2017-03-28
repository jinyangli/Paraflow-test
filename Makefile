all : blastest mkltest 

blastest:
	gcc blastest.c -o blastest -lrt -lgslcblas

mkltest:	
	 gcc -m64 -static mkltest.c -o mkltest -I/opt/intel/mkl/include -Wl,--start-group -L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_core  -lmkl_intel_thread -Wl,--end-group -L/opt/intel/compilers_and_libraries/linux/lib/intel64 -liomp5 -ldl -lm -lpthread
