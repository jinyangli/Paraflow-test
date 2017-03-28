#!/usr/bin/python
import numpy as np
import sys
import timeit

def main():
    n = 1000
    print len(sys.argv)
    if len(sys.argv) > 1:
        print sys.argv[1]
        n = int(sys.argv[1])
    matA = np.random.rand(n,n) 
    matB = np.random.rand(n,n) 
    dur = timeit.timeit(lambda: np.dot(matA, matB), number=1)
    print dur

if __name__ =='__main__':
    main()
