#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Funcion a integrar
double function(double x){
	return (exp(-x*x)); 
}
// Polinomios de Legendre
double P2(double x){
	return (x*x-(1.0/3.0));
}

double P3(double x){
	return (x*x*x-(3.0/5.0)*x);
}

double P4(double x){
	return (x*x*x*x-(6.0/7.0)*x*x+(3.0/35.0)); 
}
// Find roots using bisection method
double bisection(int n, double f(double x), double a, double b, double TOL, int maxiter){
	double c; 
	if (f(a)*f(b)<=0){
		int iter = 1; 
		do{
			c = (a+b)/2.0;
			if (f(a)*f(c) > 0) a = c; 
			else if (f(a)*f(c) < 0) b = c; 
			else if (f(c) == 0) return c; 
			iter ++;
		}
		while (fabs(a-b)>=TOL && iter<=maxiter);
		return c; 
	}
	else{
		return 55; 
	}
}

double Li(int n, double x, double xi[], int i){
	int j; 
	double prod = 1.0;
	for (j=0; j<n; j++){
		if (i!=j){
			prod *= (x-xi[j])/(xi[i]-xi[j]); 
		}
	}
	return prod;	
}


// Solve Ci
double *roots(int n, double f(double x)){
	// find roots
	int i = 0, j;
	double *xi;
	xi = (double*)malloc(sizeof(double)*n); 
	
	double hh = 0.01, x, root; 
	for (x=-1.0; x<=1.0; x=x+hh){
		root = bisection(n, f, x, x+hh, 0.00000001, 10000); 
		if (root!=55){
			xi[i] = root; 
			i++; 
		}
	}
	return xi; 
}

double Ci(int n, double f(double x), int raiz){
	int i, j; 
	double *xi;
	xi = roots(n, f); 
	//printf("\n xi: %f", xi[raiz]);
	
	double a = -1.0, b = 1.0, h, suma = 0.0, x; 
	int N = 100; 
	double A = Li(n, a, xi, raiz), B = Li(n, b, xi, raiz); 
	h = (b-a)/N; 
	
	for (i=1; i<N; i++){
		x = a + i*h; 
		if (i%2 == 0){
			suma += 2*Li(n,x, xi, raiz); 
		}
		else {
			suma += 4.0*Li(n, x, xi, raiz); 
		} 
	}
	return ((1.0/3.0)*h*(suma + A + B) );  
	
}

double GaussQuadra(int n, double a, double b, double grado(double x)){
	double *xi;
	xi = roots(n, grado); 
	
	double c = (b-a)/2.0; 
	double sum = 0.0;  
	for (int i=0; i<n; i++){
		sum += Ci(n, grado, i)*function( ((b-a)/2.0)*xi[i]+(a+b)/2.0); 
	}
	
	double integral = (sum)*(b-a)/2.0;  
	return integral; 
}

int main(){
	clock_t start = clock(); 
	
	int n = 4; // debe coincidir con el polinomio de Legendre que se escoja: n=2->P2, n=3->P3; n=4->P4. 
	double res; 
	res = GaussQuadra(n, 1.0, 1.5, P4); 
	printf("\n Para tres nodos: %0.9f", res); 
	
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 
	return 0; 

}
