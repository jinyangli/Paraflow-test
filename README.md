Testing Matrix multiplication Performance

# How to Run
`KMP_AFFINITY="explicit,granularity=fine,proclist=[0,1,2,3]" ./mkltest`

# Example output
Below is an example output on our latest GPU machines. When sharding the matrix multiplication 16-way, we can potentially get 15X-22X speedup.

```$ KMP_AFFINITY="explicit,granularity=fine,proclist=[0,1,2,3,4,5,6,7,8,9,10,11]" ./mkltest                              
MKL matrix multiply two 8192 x 8192 matrixes
----------row partition----------------
1       2       4       8       16
5343.5  2415.4  1338.9  619.3   342.8
1.0     2.2     4.0     8.6     15.6
----------column partition (with accumulation)-------------
1       2       4       8       16
5221.0  2532.9  1019.3  549.8   314.6
1.0     2.1     5.1     9.5     16.6
----------column partition (w/o accumulation)-------------
1       2       4       8       16
5117.1  2363.3  916.6   458.2   223.5
1.0     2.2     5.6     11.2    22.9
```


# Reducing Performance variation

Setting the `KMP_AFFINITY` environmental variable constrains the OpenMP processes to run on cores 0,1,2,3. Running on physical cores only 
seems to reduce performance variation.

One should also reduce performance variation by disabling frequence scaling. Below are the steps:

`sudo apt-get install linux-tools-generic`

`sudo cpupower frequency-set --governor performance` 

To check the measured frequence, do 

`cpupower --cpu all frequency-info --freq --human`

Unfortunately, the measured frequencies still vary on my desktop after the above steps and the performance results incur quite a bit of variation from 
run to run.





