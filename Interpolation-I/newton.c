#include <stdio.h>
#include <stdlib.h>
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

double **matrizNewton(int N, double datosX[]){
	int rows = N; 
	
	double **array; 
	array = (double**)malloc(rows*sizeof(double*));
	for (int i=0; i<rows; i++){
		array[i] = (double*)malloc(rows*sizeof(double));
	}
	
	int i, j, k;
	double p;  
	for (i=0; i<rows; i++){
		array[i][0] = 1.0; 
		for (j=1; j<rows; j++){
			p = 1; 
			if (i>=j){
				for (k=0; k<j; k++){
					p = p*(datosX[i]-datosX[k]);
				}
				array[i][j] = p;
			}
			else{
				array[i][j] = 0.0; 
			}
		}
	}
	return array; 
}

void freeMatriz(double **matriz, int rows){
	int i;
	for (i=0; i<rows; i++){
		free(matriz[i]);
	}
	free(matriz); 
}

double *coefNewton(int N, double datosX[], double datosY[]){
	double **matrizNew, *x;
	matrizNew = matrizNewton(N, datosX);
	x = triangular_inferior_to_x(matrizNew, N, datosY);
	
	freeMatriz(matrizNew, N);
	return x; 
}

void save_vector(double *vec, int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f\n", vec[i]); 
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
	int size = 1000;
	double x[size], y[size]; 
	
	arrRandom(x, size, -1, 1); 
	arrEval(y, x, size); 
	
	int grado = 10; 
	double *coefNew; 
	coefNew = coefNewton(grado,x, y); 
	saveArray(x, y, size, "ej4_n1000.txt");
	save_vector(coefNew, grado, "ej4_n1000_coef.txt"); 

	
	return 0; 
}
