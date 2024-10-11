#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include "funciones_iteracion.h"
#define PI 3.141592654


double dot_product_col_mat(int n, double **matriz, int col, int col2){
    double suma = 0;
    for (int i=0; i<n; i++){
        suma += matriz[i][col]*matriz[i][col2]; 
    }
    return suma; 
}

void normalizar_col_mat(int n, double **matriz, int col){
    double suma = 0;
    for (int i=0; i<n; i++){
        suma += matriz[i][col]*matriz[i][col]; 
    }
    suma = sqrt(suma);
    for (int i=0; i<n; i++){
        matriz[i][col] = matriz[i][col]/suma; 
    }
}


double **gram_schimdt(int n, double **matriz, int filas, int cols){
    int i, j, k; 
    for (i = 0; i<cols; i++){
        for (j = 0; j<i; j++){
            double proj = dot_product_col_mat(n, matriz, j, i)/dot_product_col_mat(n, matriz, j, j); 
            for (k =0; k<filas; k++){
                matriz[k][i] = matriz[k][i] -proj*matriz[k][j]; 
            }
        }
        normalizar_col_mat(n, matriz, i); 
    }
    return matriz; 
}

double **matriz_identidad_no_cuadrada(int filas, int cols){
    double **identidad_no_cuadrada = matriz_vacia(filas, cols);
    for (int i=0; i<filas; i++){
        identidad_no_cuadrada[i][i] = 1.0;
    }
    return identidad_no_cuadrada; 
}

double max(int filas, int cols,  double **a){
    //generar los inicializadores de forma aleatoria  
    
    int i = 1, j = 2; 
    double maximo;
    maximo = a[i][j]; 

    for (i = 0; i<filas; i++){
        for (j=0; j<cols; j++){
            if (i!=j){
                if (fabs(a[i][j]) > fabs(maximo)){
                    maximo = a[i][j]; 
                }
            }
        }
    }
    return maximo; 
}

void save_vector(double **matriz, int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f\n", matriz[i][i]); 
		}
}


double **matriz_eigenvalores(double **A, int cant_eigen, int filas, int cant_iter_jacobi, double TOL){
		double **X, **Z, **ZT, **B, **matriz_jacobi;  
		X = matriz_identidad_no_cuadrada(filas, cant_eigen); 
		double maxB;  
		for (int i=0; i<200; i++){
			//printf("\n Iteracion i: %i\n", i); 
			Z = matmul(A, X, filas, cant_eigen, filas); 
			Z = gram_schimdt(filas, Z, filas, cant_eigen); 
			ZT = matriz_transpuesta(Z, filas, cant_eigen); 


			B = matmul(A, Z, filas, cant_eigen, filas);
			B = matmul(ZT, B, cant_eigen, cant_eigen, filas); 

			maxB = max(cant_eigen, cant_eigen, B);   
			
			if (fabs(maxB) < TOL){
				break; 
			}

			matriz_jacobi = metodo_jacobi_eigenvalores(B, cant_eigen, cant_iter_jacobi);  
			X = matmul(Z, matriz_jacobi, filas, cant_eigen, cant_eigen);
		}
		return B; 
	}





int main(){
	//Tiempo
	clock_t start = clock(); 

    //Leer la matriz
    int filas, cols; 
    FILE *mat_file; 
    mat_file = fopen("Eigen_50x50.txt", "r");
    fscanf(mat_file, "%d%d\n", &filas, &cols);
    double **A;
    A = (double**)malloc(filas * sizeof(double*)); 
    for (int i=0; i<filas; i++){
        A[i] = (double*)malloc(cols * sizeof(double)); 
    }

    for(int i = 0; i < filas; i++){
	    for(int j = 0; j < cols; j++){
	        fscanf(mat_file, "%lf", &A[i][j]);
	    }
	}




    int cant_eigen = 5; 
    double TOL = 0.0001; 
    double **B; 
    B = matriz_eigenvalores(A, cant_eigen, filas, 40, TOL); 
    
	save_vector(B, cant_eigen, "eigen_50x50_potencia.txt"); 
    //imprimir_matriz(B, cant_eigen, cant_eigen); 
    
    
    clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds); 
    

	freeMatrix(B, cant_eigen); 
	return 0; 
}
