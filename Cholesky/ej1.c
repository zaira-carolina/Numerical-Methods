#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 
#include "read_matrices_vectors.h"
#include "metodo_cholesky.h"
#include <time.h>



int main(){


    time_t begin, end;
    time(&begin);

    int N = 4; 
    double **array, **L, **LT; 
    array = read_matriz(N, "ej1_matriz1.txt");
    L = L_Cholesky(array, N);  
    LT = matriz_transpuesta(L, N);

    //para imprimir
    printf("Matriz a descomponer: \n");
    imprimir_matriz2(array, N); 
    printf("\n"); 
    printf("Resultado y traspuesta\n"); 
    imprimir_matriz2(L, N); 
    printf("\n"); 
    imprimir_matriz2(LT, N); 

    time(&end);
    time_t elapsed = end - begin;
    printf("Tiempo en segundos: %lf.\n", elapsed);
    return 0; 
}