#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

double *CoefPolinomio(double datosX[], double datosY[], int degree, int *terminos){
	double **X, **XT, **A, *b, **L, **U, *coef; 
	int N = degree+1; 
		
	X = matrizMinimos(degree, datosX);
	XT = matriz_transpuesta(X, N, N); 
	A = matmul(XT, X, N, N, N); 	
	b = prod_matvec(XT, datosY, N); 
	L = matriz_vacia(N, N);
	U = matriz_vacia(N, N); 
	
	LU_matrix(A, L, U, N, N);
	coef = triangular_superior_to_x(U, N, triangular_inferior_to_x(L, N, b));
	*terminos = N; 
		
	freeMatriz(L, N);
	freeMatriz(U, N);
	free(b);
	freeMatriz(A, N);
	freeMatriz(XT, N);
	freeMatriz(X, N);
 
	return coef; 
}

double *CoefPolinomioFun(double datosX[], double datosY[], int degree, int *terminos){
	double **X, **XT, **A, *b, **L, **U, *coef; 
	int N = degree+1; 
		
	X = matrizMinimosFun(degree, datosX);
	XT = matriz_transpuesta(X, N, N); 
	A = matmul(XT, X, N, N, N); 	
	b = prod_matvec(XT, datosY, N); 
	L = matriz_vacia(N, N);
	U = matriz_vacia(N, N); 
	
	LU_matrix(A, L, U, N, N);
	coef = triangular_superior_to_x(U, N, triangular_inferior_to_x(L, N, b));
	*terminos = N; 
		
	freeMatriz(L, N);
	freeMatriz(U, N);
	free(b);
	freeMatriz(A, N);
	freeMatriz(XT, N);
	freeMatriz(X, N);
 
	return coef; 
}


void saveArray(double x[], double y[], int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f %f\n", x[i], y[i]); 
	}
}


void save_vector(double *vec, int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f\n", vec[i]); 
	}
}


int main(){
	
	int size = 1000;
	double x[size], y[size]; 
	
	arrRandom(x, size, -1, 1); 
	arrEval(y, x, size); 
	saveArray(x, y, size, "ej1_datos_n1000_v1.txt"); 
	
	double *coef_min; 
	int N; 
	
	int lista[] = {1, 2, 3, 4}; 
	for (int num = 0; num<4; num++){
		printf("\n grado: %i", num+1); 
		coef_min = CoefPolinomio(x, y, lista[num], &N); 
		for (int i = 0; i<N; i++){
			printf("\n %f", coef_min[i]); 
		}
		//save_vector(coef_min, N, "ej1_linea_n5_v1.txt"); 
	}
	
	// PARA LA COMBINACION DE FUNCIONES
	double *coef_min_fun;
	int M; 
	coef_min_fun = CoefPolinomioFun(x, y, 2, &M);
	printf("\n Para la combinación de funciones: ");
	for (int i = 0; i<M; i++){
		printf("\n %f ", coef_min_fun[i]); 
	} 
	
	return 0; 
}
