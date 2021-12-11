#include "../include/sequential.h"

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

void organize_into_buckets(int* input_array, int size, int **buckets, int *bucket_fill, int number_buckets, int minimum_value, int maximum_value) {
    int bucket_increment = (maximum_value - minimum_value)/number_buckets+1;
    for (int i = 0; i< number_buckets; i++) { //Enchimento de todos os baldes começa a 0
        bucket_fill[i] = 0;
    }
    for (int i=0 ; i < size; i++) {
        for (int bucket = 0; bucket < number_buckets; bucket++) {
            int current_value = input_array[i];
            if (current_value >= minimum_value + bucket_increment* bucket && current_value < minimum_value + bucket_increment* (bucket+1)) {
                buckets[bucket][bucket_fill[bucket]]=current_value;
                bucket_fill[bucket]++;
            }
        }
    }
}

void sort_buckets(int **buckets, int *bucket_fill, int number_buckets, int *sorted_bucket) {
    int numbers_checked = 0;
    for (int bucket_id = 0; bucket_id < number_buckets; bucket_id++) {
        quick_sort(buckets[bucket_id], bucket_fill[bucket_id], sorted_bucket + numbers_checked);
        numbers_checked += bucket_fill[bucket_id];
    }
}

void sequential(int* input_array, int* output_array, int size) {
    int min, max, number_buckets, **buckets;

    initialize_buckets(input_array, size, &number_buckets, &buckets, &min, &max); //Inicializa os buckets
    int bucket_fill[number_buckets];
    organize_into_buckets(input_array, size, buckets, bucket_fill, number_buckets, min, max); // Organiza cada elemento no seu bucket
    sort_buckets(buckets, bucket_fill, number_buckets, output_array);
    
    //freeing allocated memmory
    for (int i =0 ;i < number_buckets; i++) {
        free(buckets[i]);
    }
    free(buckets);
}