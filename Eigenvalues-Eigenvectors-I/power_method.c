#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "funciones.h"

double **potencia_eigen(int cant_eigenvalores, int N, double TOL, double **matriz){
        double **array, *v0, *v1;
        array = matriz_vacia(N,N);
        
        for (int n=0; n<cant_eigenvalores; n++){ //ciclo para el número de eigenvalores a calcular

            v0 = vector_vacio(N, 0.2); 
            v0 = normalizar2(v0, N); 
            v1 = vector_vacio(N, 0.0);
            
            double error = pow(10, 10); 
            double valor_viejo = 0.0,  valor_nuevo = 0 ; 
            double constante;
                    
            while (error > TOL){

                for (int i=0; i<N; i++){
                    for (int k=0; k<n; k++){
                        v0[i] -= vector_vector(v0, array[k], N)*array[k][i];
                    }
                }
                
                
                for (int i=0; i<N; i++){
                    *(v1 + i) = *(matriz_vector(matriz, v0, N)+i); 
                }

                valor_nuevo = vector_vector(v0, v1, N);  
                error = fabs(valor_nuevo - valor_viejo); 
                v1 = normalizar(v1, N, &constante); 
                
                valor_viejo = valor_nuevo; 

                for (int i=0; i<N; i++){
                    *(v0+i) = *(v1+i); 
                    }
        
                }
                
                //printf("\n eigenvalor: %f \n", constante); 
                for (int k=0; k<N; k++){
                    array[n][k] = v0[k]; 
                    }
            //printf("\n Eigenvalor %f ", valor_nuevo);  
            printf("\n Eigenvalor %f ", constante); 
            }
        return array; 
}

double **matriz_tridiagonal(double valor_a, double valor_b, int N){
    double **matriz_tridiagonal; 
    double *alpha, *beta; 

    matriz_tridiagonal = matriz_vacia(N, N);
    alpha = vector_vacio(N, valor_a);  //valor diagonal
    beta = vector_vacio(N, valor_b); //valor al lado de la diagonal principal

    for (int i = 0; i<=N-1; i++){
        *(*(matriz_tridiagonal + i) + i) = *(alpha+i); 
        if ((i+1) < N){
            *(*(matriz_tridiagonal + i + 1)+i) = *(beta + i);
            *(*(matriz_tridiagonal + i) + i+1) = *(beta + i); 
        }  
    }
    return matriz_tridiagonal; 
}

int main(){
    clock_t start = clock();
    int N = 1000; 
    double TOL = pow(10, -2); 
	
	double **matriz; 
    matriz = matriz_tridiagonal(2.0, 1.0, N);

    //printf("\n");
    //imprimir_matriz(matriz, N); 
    //printf("\n");


    double **array;
    array = matriz_vacia(N,N); 
    array = potencia_eigen(1, N, TOL, matriz); 
    
    char *nombreArchivo = "vector_propio_N_1000_v4.txt";
    char *modo = "w";// w es para sobrescribir, a+ es para añadir al existente
    FILE *archivo = fopen(nombreArchivo, modo);
    for (int i=0; i<N; i++){
        fprintf(archivo, "%f\n", array[0][i]);
    }

    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    printf("\nSegundos: %f", seconds); 

    free(matriz); 
    free(array); 
}