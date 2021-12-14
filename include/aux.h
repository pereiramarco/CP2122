#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

long int get_current_time();
void initialize_buckets(int * input_array, int size, int *number_buckets, int *** buckets, int *min, int *max);
void quick_sort(int *bucket, int bucket_size, int *sorted_bucket);