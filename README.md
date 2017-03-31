Testing Matrix multiplication Performance

# How to Run
`KMP_AFFINITY="explicit,granularity=fine,proclist=[0,1,2,3]" ./mkltest`

# Reducing Performance variation

Setting the `KMP_AFFINITY` environmental variable constrains the OpenMP processes to run on cores 0,1,2,3. Running on physical cores only 
seems to reduce performance variation.

I also tried to reduce performance variation by disabling frequence scaling. Below are the steps:
`sudo apt-get install linux-tools-generic`
`sudo cpupower frequency-set --governor performance` 
To check the measured frequence, do 
`cpupower --cpu all frequency-info --freq --human`

Unfortunately, the measured frequencies still vary on my desktop after the above steps and the performance results incur quite a bit of variation from 
run to run.





