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
        buckets[bucket][bucket_fill[bucket]]=input_array[i];
        bucket_fill[bucket]++;
    }
    //printf("Buckets organized\n");
}

void sort_buckets_parallel(int **buckets, int *bucket_fill, int number_buckets) {
    int bucket_id;    
    #pragma omp parallel for 
    for (bucket_id = 0; bucket_id < number_buckets; bucket_id++) {
        quick_sort(buckets[bucket_id], 0, bucket_fill[bucket_id]);
    }
}

void parallel(int* input_array, int* output_array, int size) {
    int min, max, number_buckets, **buckets;

    initialize_buckets(input_array, size, &number_buckets, &buckets, &min, &max); //Inicializa os buckets
    int bucket_fill[number_buckets];
    organize_into_buckets_parallel(input_array, size, buckets, bucket_fill, number_buckets, min, max); // Organiza cada elemento no seu bucket
    sort_buckets_parallel(buckets, bucket_fill, number_buckets);
    //freeing allocated memmory
    int i,j,total_i;
    total_i = 0;
    for (i = 0 ;i < number_buckets; i++) {
        for (j = 0; j < bucket_fill[i]; j++) {
            output_array[total_i] = buckets[i][j];
            total_i++;
        }
        free(buckets[i]);
    }
    free(buckets);
}