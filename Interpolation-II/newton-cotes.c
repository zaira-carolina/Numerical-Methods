#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double function(double x){
	return (log(4*x*x+4)); //(exp(x*x));
}

double newtonCotes(double a, double b, int n, double coef[], int cantIntervalos){
	int i, j; 
	double newtonCoef[6] = {1.0/2.0, 1.0/3.0, 3.0/8.0, 2.0/45.0, 5.0/288.0, 1.0/140.0}; 
	
	double hspace = (b-a)/cantIntervalos; 
	double h = (hspace/n),  xintervalo; 
	double sumaTotal = 0, res, suma;
	
	for (i=0; i<cantIntervalos; i++){
		suma = 0; 
		for (j=0; j<(n+1); j++){
			xintervalo = a + j*h; 
			suma += coef[j]*function(xintervalo); 
		}
		sumaTotal += suma;
		a = a + hspace; 
	}
	res = newtonCoef[n-1]*h*sumaTotal;
	return res;  
}


void SolveInt(int cantIntervalos, int n, double a, double b){
	
	double Coef[n+1];
	int i; 
	 
	switch (n){
		case 1:
			Coef[0] = 1.0, Coef[1] = 1.0; 
			break;
		case 2: 
			Coef[0] = 1.0, Coef[1] = 4.0, Coef[2] = 1.0;
			break; 
		case 3:
			Coef[0] = 1.0, Coef[1] = 3.0, Coef[2] = 3.0, Coef[3] = 1.0; 
			break;
		case 4: 
			Coef[0] = 7.0, Coef[1] = 32.0, Coef[2] = 12.0, Coef[3] = 32.0, Coef[4] = 7.0; 
			break; 
		case 5: 
			Coef[0] = 19.0, Coef[1] = 75.0, Coef[2] = 50.0, Coef[3] = 50.0, Coef[4] = 75.0, Coef[5] = 19.0;
			break;
		case 6:
			Coef[0] = 41.0, Coef[1] = 216.0, Coef[2] = 27.0, Coef[3] = 272.0, Coef[4] = 27.0, Coef[5] = 216.0, Coef[6] = 41.0; 
			break; 
		default:
			printf("Newton-Cotes no está definido para este polinomio"); 
	}
	
	double res = newtonCotes(a, b, n, Coef, cantIntervalos);
	printf("\nAproximación integral: %0.9f\n", res); 
}




int main(){
	clock_t start = clock(); 
	
	int cantIntervalos = 10;
	int n = 1;
	double a = -3.0, b = 3.0; 

	printf("\n Para 10 intervalos \n"); 
	for (int i=1; i<7; i++){
		printf("\n n = %i", i);
		SolveInt(cantIntervalos, i, a, b); 
	}
	
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 
	
	return 0; 
}
