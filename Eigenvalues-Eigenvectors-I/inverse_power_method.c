#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "funciones.h"

double **eigenvalor_chico(int cant_eigenvalores, double **L, double **LT, int N, double TOL){

    double **array;
    array = matriz_vacia(N,N);
    
    int i, j; 
    
    for (int n = 0; n<cant_eigenvalores; n++){
        //printf("\n n: %i", n); 

        double *v0, *v1; 
        v0 = vector_vacio(N, 1.0); 
        v0 = normalizar2(v0, N); 
        v1 = vector_vacio(N, 0.0);
        double lambda, lambda_old = pow(10, 20);
        double valor = 1.0; 
        
        while (fabs(valor)>TOL){
            
            for (int i=0; i<N; i++){
                    for (int k=0; k<n; k++){
                        v0[i] -= vector_vector(v0, array[k], N)*array[k][i];
                    }
                }


            v1 = triangular_superior_to_x(LT, N, triangular_inferior_to_x(L, N, v0)); 
            double suma = 0; 
            for (i=0; i<N; i++){
                suma += v0[i]*v1[i];
            }
            lambda = (1/suma); 
            valor = fabs(lambda-lambda_old); 
            v1 = normalizar2(v1, N);

            for (i=0; i<N; i++){
                v0[i] = v1[i];
            }
            lambda_old = lambda; 
        }
    printf("\n Eigenvalor %i : %f", n,  lambda); 

    for (int k=0; k<N; k++){
		array[n][k] = v0[k]; 
	    }
    
    }
     return array; 
}

int main(){
     clock_t start = clock();

    int N = 1000;
    double **L, **LT, *alpha, *beta, *v0, *v1; 
    double TOL = pow(10, -5); 


    L = matriz_vacia(N, N); 
    alpha = vector_vacio(N, 2.0); 
    beta = vector_vacio(N, 1.0);
    L = LL_factorizacion(L, N, alpha, beta); 
    LT = matriz_transpuesta(L, N); 

    // Aqui se guardan los eigenvectores, los eigenvalores sólo se imprimen (por ahora). 
    double **array;
    array = matriz_vacia(N,N);
    array = eigenvalor_chico(5, L, LT, N, TOL); 

    //printf("\n"); 
    //for (int i =0; i<N; i++){
    //    printf("\n%f ", array[0][i]); 
    //}

    //char *nombreArchivo = "vector_propio_N_1000_inversa_positiva.txt";
    //char *modo = "w";// w es para sobrescribir, a+ es para añadir al existente
    //FILE *archivo = fopen(nombreArchivo, modo);
    //for (int i=0; i<N; i++){
    //    fprintf(archivo, "%f\n", array[0][i]);
    //} 


    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    printf("\nSegundos: %f", seconds); 

}