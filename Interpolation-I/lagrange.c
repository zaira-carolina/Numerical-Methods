#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

double *Lagrange(int cant_datos, double dataX[], double dataY[], int N, double x[]){
	double *res;
	res = (double*)malloc(cant_datos*sizeof(double)); 
	
	double y, l; 
	int i, j, k; 
	for (k = 0; k<cant_datos;  k++){
		for (i=0; i<N; i++){
			l = 1.0; 
			for (j=0; j<N; j++){
				if (i!=j){
					l *= (x[k]-dataX[j])/(dataX[i]-dataX[j]); 
				}
			}
			y += l*dataY[i]; 
		}
		res[k] = y; 
		//printf("y: %f ", y);
	}
	return res; 
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
	clock_t start = clock(); 
	
	int size = 1000;
	double x[size], y[size]; 
	
	arrRandom(x, size, -1, 1); 
	arrEval(y, x, size); 
	saveArray(x, y, size, "ej3_n1000.txt"); 
	
	//double X[5] = {1, 2, 3, 4, 5};
	//double Y[5] = {1, 4, 9, 16, 25}; 
	//double xrand[5] = {6, 7, 8, 9, 10}; 
	
	int cantDatosInterpolar = 2;
	double xvalues[cantDatosInterpolar];
	arrRandom(xvalues, cantDatosInterpolar, -1, 1); 
	
	double *resLagrange, *resLagrangeError;
	//resLagrange = Lagrange(cantDatosInterpolar, x, y, size, xvalues);
	//saveArray(x, resLagrange, cantDatosInterpolar, "ej3_n10_interpolar.txt"); 
	
	resLagrangeError = Lagrange(size, x, y, size, x);
	save_vector(resLagrangeError, size, "ej3_n1000_error.txt"); 
	
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds); 
}
