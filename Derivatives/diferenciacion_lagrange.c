#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

double funcion(double x){
	return (sin(x)); 
}

double antix(double x){
	return (cos(x)); 
}

double *pointx(int n, double a, double b){
	double *arrayx; 
	arrayx = (double*)malloc(n*sizeof(double)); 

	double h = (b-a)/n; 
	for (int i=0; i<n; i++){
		arrayx[i] = a+i*h; 
	}
	return arrayx; 
}

double *pointxLagrange(int n, double a, double b, double error){
	double *arrayx; 
	arrayx = (double*)malloc(n*sizeof(double)); 

	double h = (b-a)/n; 
	for (int i=0; i<n; i++){
		arrayx[i] = a+i*h+error; 
	}
	return arrayx; 
}




double *pointy(int n, double x[], double(*funcion)(double)){
	double *arrayy;
	arrayy = (double*)malloc(n*sizeof(double));
	for (int i=0; i<n; i++){
		arrayy[i] = (*funcion)(x[i]);
	}
	return arrayy; 
}

double derivadax(double xeval, int n, double x[], double y[]){
	double prod, suma_derivada, suma = 0.0;
	int i, j; 
	
	for (i=0; i<n; i++){
		prod = 1.0; 
		suma_derivada = 0.0; 
		for (j=0; j<n; j++){
			if (i!=j){
				prod *= (xeval-x[j])/(x[i]-x[j]);
				suma_derivada += 1/(xeval-x[j]); 
			
			}
		}
		suma += y[i]*prod*suma_derivada; 	
	}
	return suma;
}

double derivadaxx(double xeval, int n, double x[], double y[]){
	double prod, suma_derivada, suma = 0.0;
	double suma_derivada2; 
	int i, j; 
	
	for (i=0; i<n; i++){
		prod = 1.0; 
		suma_derivada = 0.0; 
		suma_derivada2 = 0.0; 
		for (j=0; j<n; j++){
			if (i!=j){
				prod *= (xeval-x[j])/(x[i]-x[j]);
				suma_derivada += 1/(xeval-x[j]); 
				suma_derivada2 += 1/((xeval-x[j])*(xeval-x[j])); 
			}
		}
		suma += y[i]*prod*((suma_derivada*suma_derivada)-suma_derivada2); 	
	}
	return suma;
	
}


double derivadaxxx(double xeval, int n, double x[], double y[]){
	double prod, suma_derivada, suma = 0.0;
	double suma_derivada2, suma_derivada3; 
	int i, j; 
	
	for (i=0; i<n; i++){
		prod = 1.0; 
		suma_derivada = 0.0; 
		suma_derivada2 = 0.0; 
		suma_derivada3 = 0.0; 
		for (j=0; j<n; j++){
			if (i!=j){
				prod *= (xeval-x[j])/(x[i]-x[j]);
				suma_derivada += 1/(xeval-x[j]); 
				suma_derivada2 += 1/((xeval-x[j])*(xeval-x[j])); 
				suma_derivada3 += 1/((xeval-x[j])*(xeval-x[j])*(xeval-x[j])); 
			}
		}
		suma += y[i]*prod*((suma_derivada*suma_derivada*suma_derivada)-3*suma_derivada*suma_derivada2+2*suma_derivada3); 	
	}
	return suma;
	
}


int main(){
	clock_t start = clock(); 

	double *x, *y, *xx;
	int n = 10; 
	double a = -1.0, b = 1.0;
	x = pointx(n, a, b); 
	y = pointy(n, x, funcion); 
	
	xx = pointxLagrange(n, a, b, 0.0001); 
	int i, j, k;
	
	
	printf("\nf'(x) = cos(x), f'(x) = aprox, f''(x) = -sin(x), f''(x) = aprox, f'''(x) = -cos(x), f'''(x) = aprox"); 
	for (int i=0; i<n; i++){
		printf("\n %0.9f, %0.9f, %0.9f, %0.9f, %0.9f, %0.9f ", antix(x[i]), derivadax(xx[i], n, x, y), -y[i], derivadaxx(xx[i], n, x, y), -antix(x[i]), derivadaxxx(xx[i], n, x, y)); 
	}
	
	printf("\n"); 
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 
	
	
	printf("\n"); 
}

