#!/bin/bash

#directory
MY=~/CP2122

#size of the random array
SORT_SIZE=10000000

#max number in the random array
MAX_NUMBER=10000000

#type of the run executed (0 for parallel, 1 for sequential)
RUN_TYPE=0

#compute partition
PARTITION=cpar

#nodelist
NODE=compute-113-17

#threads
THREADS=16

module load papi/5.4.1
export OMP_NUM_THREADS=$THREADS
srun --partition=$PARTITION --nodelist=$NODE $MY/sort $SORT_SIZE $MAX_NUMBER $RUN_TYPE
