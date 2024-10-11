#include <stdio.h> 
#include <stdlib.h>
#include "read_matrices_vectors.h"
#include <math.h> 
#include <time.h>

int main(){

    clock_t start = clock();
    
    double **matriz_tridiagonal; 
    double *alpha, *beta; 

    int N = 50;

    
    //Crear la matriz tridiagonal
    double h = 1.0/(N+1); 
    matriz_tridiagonal = matriz_vacia(N, N);
    alpha = vector_vacio(N, 2.0); 
    beta = vector_vacio(N, -1.0);
    double valor = 2.0; 
    double primera_condicion = 0.0, segunda_condicion = 2.0; 
    
    double b_sol[N]; 
    b_sol[0] = (valor - (primera_condicion)/(h*h))*(h*h); 
    b_sol[N-1] = (valor - (segunda_condicion)/(h*h))*(h*h);
    for (int i=1; i < N-1; i++){
            b_sol[i] = valor*(h*h); 
    }

    for (int i = 0; i<N-1; i++){
        *(*(matriz_tridiagonal + i) + i) = *(alpha+i); 
        if ((i+1) < N){
            *(*(matriz_tridiagonal + i + 1)+i) = *(beta + i);
            *(*(matriz_tridiagonal + i) + i+1) = *(beta + i); 
        }  
    }
    // hasta aqui se crea la matriz tridiagonal




    //factorización de la matriz
    double **L = matriz_vacia(N, N); 
    *(*L) = sqrt(*(alpha)); 
    for (int i = 0; i<N; i++){
            if ((i+1)<N){
            *(*(L + i + 1) + i) = (*(beta + i))/(*(*(L + i) + i));
            *(*(L + i + 1) + i+1) = sqrt(*(alpha + i + 1)-(*(*(L + i + 1) + i))*(*(*(L + i + 1) + i))); 
        }
    }
    

    //Resolver
    double **LT = matriz_vacia(N, N); 
    LT = matriz_transpuesta(L, N);
    double *y;
    y = triangular_inferior_to_x(L, N, b_sol); 
    double *x; 
    x = triangular_superior_to_x(LT, N, y);


    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    printf("\nSegundos: %f", seconds); 
    return 0; 
}