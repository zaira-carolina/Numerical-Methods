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

double *pointy(int n, double x[], double(*funcion)(double)){
	double *arrayy;
	arrayy = (double*)malloc(n*sizeof(double));
	for (int i=0; i<n; i++){
		arrayy[i] = (*funcion)(x[i]);
	}
	return arrayy; 
}

	
double derivadax(double h, double x){
	return (funcion(x+h)-funcion(x))/h; 
}

double derivadaxx(double h, double x){
	return  (funcion(x+h)-2*funcion(x)+funcion(x-h))/(h*h);
}

double derivadaxxx(double h, double x){
	return (funcion(x+2*h)-2*funcion(x+h)+2*funcion(x-h)-funcion(x-2*h))/(2*h*h*h);
}


int main(){
	clock_t start = clock(); 
	
	double *x, *y, *yprime; 
	int n = 10; 
	double a = -1.0, b = 1.0;
	x = pointx(n, a, b); 
	y = pointy(n, x, funcion); 
	yprime = pointy(n, x, antix);
	
	double h = 0.001;
	double xder[n], xxder[n], xxxder[n]; 
	for (int i=0; i<n; i++){
		xder[i] = derivadax(h, x[i]);  
		xxder[i] = derivadaxx(h, x[i]); 
		xxxder[i] = derivadaxxx(h, x[i]); 
	}
	
	
	
	printf("\nf'(x) = cos(x), f'(x) = aprox, f''(x) = -sin(x), f''(x) = aprox, f'''(x) = -cos(x), f'''(x) = aprox"); 
	for (int i=0; i<n; i++){
		printf("\n %0.9f, %0.9f, %0.9f, %0.9f, %0.9f, %0.9f ", yprime[i], xder[i], -y[i], xxder[i], -yprime[i], xxxder[i]); 
	}
	
	

	printf("\n"); 
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 
	
	return 0; 
}
