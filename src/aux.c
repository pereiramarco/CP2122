#include "../include/aux.h"

long int get_current_time() {
    struct timeval time;
    gettimeofday(&time,NULL);

    return time.tv_sec * 1000 + time.tv_usec / 1000;
}

void quick_sort(int *bucket, int bucket_size, int *sorted_bucket) {
    if (bucket_size==0) {
        return;
    }
    if (bucket_size==1) {
        sorted_bucket[bucket_size-1] = bucket[0];
        return;
    }
    int bucket_1[bucket_size], bucket_2[bucket_size];
    int bucket_1_fill=0, bucket_2_fill=0;
    int last_element = bucket[bucket_size-1];
    for (int i=0; i < bucket_size-1; i++) {
        if (bucket[i] < last_element) {
            bucket_1[bucket_1_fill++]=bucket[i];
        }
        else {
            bucket_2[bucket_2_fill++]=bucket[i];
        }
    }
    quick_sort(bucket_1, bucket_1_fill, sorted_bucket);
    sorted_bucket[bucket_1_fill] = last_element;
    quick_sort(bucket_2, bucket_2_fill, sorted_bucket + bucket_1_fill + 1);
}

void initialize_buckets(int * input_array, int size, int *number_buckets, int *** buckets, int *min, int *max) {
    *max=input_array[0], *min=input_array[0];
    for (int i = 1; i < size; i++) {
        if (input_array[i] > *max) {
            *max = input_array[i];
        }
        else if (input_array[i] < *min) {
            *min = input_array[i];
        }
    }
    //Creating buckets
    *number_buckets = round(sqrt(size));
    *buckets = malloc(*number_buckets*sizeof(int*));

    printf("Mininum_Value: %d Maximum_Value: %d\n",*min,*max);
    for (int i =0 ;i <*number_buckets; i++) {
        (*buckets)[i]=malloc(0.5*size*sizeof(int));
    }
    printf("Buckets created\n");
}