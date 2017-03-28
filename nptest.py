#!/usr/bin/python3
import numpy as np
import sys
import timeit

def main():
    n = 1000
    if len(sys.argv) > 1:
        n = int(sys.argv[1])
    print("Matrix size %d" % n)
    matA = np.random.rand(n,n) 
    matB = np.random.rand(n,n) 
    dur = timeit.timeit(lambda: np.dot(matA, matB), number=1)
    print(dur)

if __name__ =='__main__':
    main()
