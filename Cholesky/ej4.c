#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "metodo_jacobi.h"
#include "read_matrices_vectors.h"
#include <time.h>
//metodo de Jacobi
int main(){

    time_t begin, end;
    time(&begin);

    double *x, *VV, **VN; 
    int N = 4; 
    double valor = pow(10, -10); 

    double **A, *b;
    A = read_matriz(N, "ej4_matriz.txt");
    b = read_b(N, "ej4_b.txt"); 

    x = jacobi(10, N, A, b, valor); 
    for (int i=0; i<N; i++){
        printf("\n%f", x[i]); 
    }
    
    
    time(&end);
    time_t elapsed = end - begin;
    printf("\nTiempo en segundos: %lf.\n", elapsed);

    return 0; 
}