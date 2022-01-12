#include "../include/parallel.h"
#include "../include/aux.h"
#include <omp.h>

void organize_into_buckets_parallel(int* input_array, int size, int **buckets, int *bucket_fill, int number_buckets, int minimum_value, int maximum_value) {
    int bucket_increment = (maximum_value - minimum_value)/number_buckets+1;
    int i;
    for (i = 0; i< number_buckets; i++) { //Enchimento de todos os baldes começa a 0
        bucket_fill[i] = 0;
    }
    for (i = 0 ; i < size; i++) {
        int bucket = (input_array[i] - minimum_value)/bucket_increment;
        buckets[bucket][bucket_fill[bucket]++]=input_array[i];
    }
    printf("Buckets organized\n");
}

void sort_buckets_parallel(int **buckets, int *bucket_fill, int number_buckets, int *sorted_bucket) {
    int checked_list[number_buckets];
    int bucket_id;
    for (bucket_id = 0; bucket_id < number_buckets; bucket_id++) {
        if (bucket_id == 0) {
            checked_list[bucket_id]=0;
        }
        else {
            checked_list[bucket_id] =checked_list[bucket_id-1] + bucket_fill[bucket_id-1];
        }
    }
    #pragma omp parallel for 
    for (bucket_id = 0; bucket_id < number_buckets; bucket_id++) {
        quick_sort(buckets[bucket_id], bucket_fill[bucket_id], sorted_bucket + checked_list[bucket_id]);
    }
}

void parallel(int* input_array, int* output_array, int size) {
    int min, max, number_buckets, **buckets;

    initialize_buckets(input_array, size, &number_buckets, &buckets, &min, &max); //Inicializa os buckets
    int bucket_fill[number_buckets];
    long int start = get_current_time();
    organize_into_buckets_parallel(input_array, size, buckets, bucket_fill, number_buckets, min, max); // Organiza cada elemento no seu bucket
    sort_buckets_parallel(buckets, bucket_fill, number_buckets, output_array);
    long int end = get_current_time();
    printf("Total Time: %ld miliseconds\n",end-start);
    //freeing allocated memmory
    int i;
    for (i = 0 ;i < number_buckets; i++) {
        free(buckets[i]);
    }
    free(buckets);
}