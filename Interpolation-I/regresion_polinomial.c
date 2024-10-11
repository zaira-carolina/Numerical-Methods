// Minimos cuadrados 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 
#include <math.h>
#include "funciones.h"

double funx(double x){
	return 1/(1+25*x*x); 
}

void arrEval(double y[], double x[], int size){
	int i;
	for (i=0; i<size; i++){
		y[i] = funx(x[i]); 
	}
}

double **matrizInicial(int degree, double datosX[]){
	int rows = degree;  
	
	double **array; 
	array = (double**)malloc(rows*sizeof(double*));
	for (int i=0; i<rows; i++){
		array[i] = (double*)malloc(rows*sizeof(double));
	}
	
	int i, j;
	for (i=0; i<rows; i++){
		array[i][0] = 1.0;
		for (j=0; j<rows; j++){
			array[i][j] = pow(datosX[i], j);
		}
	}
	return array; 
}

void imprimirMatriz(double **matriz, int rows, int cols){
	int i, j; 
	for (i=0; i<rows; i++){
		for (j=0; j<cols; j++){
			printf("%f ", matriz[i][j]);
		}
		printf("\n"); 
	}
}

void freeMatriz(double **matriz, int rows){
	int i;
	for (i=0; i<rows; i++){
		free(matriz[i]);
	}
	free(matriz); 
}

double *CoefPolinomio(double datosX[], double datosY[], int degree){
	double **X, **XT, **A, *b, **L, **U, *coef; 
	int N = degree;
	
	 	
	X = matrizInicial(degree, datosX);
	L = matriz_vacia(N, N);
	U = matriz_vacia(N, N); 
	
	LU_matrix(X, L, U, N, N);
	coef = triangular_superior_to_x(U, N, triangular_inferior_to_x(L, N, datosY));
		
	freeMatriz(L, N);
	freeMatriz(U, N);
	freeMatriz(X, N);
 
	return coef; 
}

double randfrom(double min, double max){
	//srand(time(0)); 
	double range = (max-min); 
	double div = RAND_MAX/range; 
	return min+(rand()/div); 
}

void arrRandom(double array[], int size, double min, double max){
	int i; 
	for (i=0; i<size; i++){
		array[i] = randfrom(min, max); 
	}
}

void saveArray(double x[], double y[], int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f %f\n", x[i], y[i]); 
	}
}


int main(){	
	
	int size = 100;
	double x[size], y[size]; 
	
	arrRandom(x, size, -1, 1); 
	arrEval(y, x, size); 
	saveArray(x, y, size, "ej1_datos_n5_v1.txt"); 
	
	
	double *coef;
	int degree = 5;   
	
	coef = CoefPolinomio(x, y, degree);
	for (int i=0; i<degree; i++){
		printf("\n %f", coef[i]);
	}	
	
	return 0; 
}
