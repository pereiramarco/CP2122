#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/sequential.h"
#include "include/parallel.h"

void print_array(int *array, int size) {
    int i;
    for (i=0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//Chamada recebe tamanho do array a ordenar e valor mais alto do array
int main(int argc, char *argv[]) {
    int *input_array,*output_array;
    int size = atoi(argv[1]);
    int max_number = atoi(argv[2]);
    int running_type = atoi(argv[3]); //tipo escolhido (sequencial(1) ou paralelo(0))
    
    //Alocação de espaço para array de input e output
    input_array = malloc(size*sizeof(int));
    output_array = malloc(size*sizeof(int));

    srand(time(NULL)); //Dar seed ao random generator para ter sempre outputs diferentes
    int i;
    for (i=0; i<size; i++) {
        input_array[i]=rand()%max_number;//randomização de um valor aleatório entre 0 e max_number
    }
    print_array(input_array,size);
    if (running_type==1) {
        printf("Running sequential version\n");
        sequential(input_array,output_array,size);
    }
    else if (running_type==0) {
        printf("Running parallel version\n");
        parallel(input_array,output_array,size);
    }
    print_array(output_array,size);

    free(input_array);
    free(output_array);

    return 0;
}