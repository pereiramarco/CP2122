#!/bin/bash

#directory
MY=~/CP2122

#size of the random array
SORT_SIZE=10000000

#max number in the random array
MAX_NUMBER=100000000

#type of the run executed (0 for parallel, 1 for sequential)
RUN_TYPE=0

#node used for running the program
NODE=compute-134-135

#number of threads
NUM_THREADS=2

module load papi/5.4.1
setenv OMP_NUM_THREADS $NUM_THREADS
srun --partition=cpar --nodelist=$NODE $MY/sort $SORT_SIZE $MAX_NUMBER $RUN_TYPE
