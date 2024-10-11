#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define PI 3.14159265358979323846

// Newton-Cotes para el grado del polinomio que solicite el usuario 


double function(double x){
	return (sin(x)); //(exp(x*x));
}

double newtonCotes(double a, double b, int n, double coef[], int cantIntervalos, double hvalue){
	int i, j; 
	double newtonCoef[6] = {1.0/2.0, 1.0/3.0, 3.0/8.0, 2.0/45.0, 5.0/288.0, 1.0/140.0}; 
	
	double hspace = (b-a)/(cantIntervalos); 
	double h = hspace/n,  xintervalo; 
	//printf("\n h: %f\n", h); 
	double sumaTotal = 0, res, suma;
	
	
	//h = h*pow(2, hvalue); 
	for (i=0; i<cantIntervalos; i++){
		suma = 0; 
		for (j=0; j<(n+1); j++){
			xintervalo = a + j*h; 
			suma += (coef[j]/pow(2, hvalue))*function(xintervalo); 
		}
		sumaTotal += suma;
		a = a + hspace; 
	}
	res = newtonCoef[n-1]*h*sumaTotal;
	return res;  
}





double SolveInt(int cantIntervalos, int n, double a, double b, double hvalue){
	
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
	
	double res = newtonCotes(a, b, n, Coef, cantIntervalos, hvalue);
	return res; 
	//printf("\nAproximación integral: %f\n", res); 
}


void extraRichardson(int cantIntervalos, int n, double a, double b, double hvalue){
	// Si se quieren eliminar potencias no pares: 
	// Para eliminar potencias cada vez más grandes, se construye una matriz tridiagonal inferior
	int i, j, aprox = 8; 
	// Matriz para las aproximaciones
	double **Laprox; 
	Laprox = (double**)malloc(sizeof(double*)*aprox); 
	for (i=0; i<aprox; i++){
		Laprox[i] = (double*)malloc(sizeof(double)*aprox); 
	}
	
	// Formula para el resultado
	
	// hvalue = [1, 2, 4, 8, 16, 32, ...]
	for (i=0; i<aprox; i++){
		Laprox[i][0] = SolveInt(pow(2, i), n, a, b, 0); 
		//Laprox[i][0] = SolveInt(cantIntervalos, n, a, b, i); 
		for (j=1; j<aprox; j++){
			if (i>=j){
				Laprox[i][j] = (pow(4, j)*Laprox[i][j-1]-Laprox[i-1][j-1])/(pow(4, j)-1); 
			}
		}
	}
	
	
	for (i=0; i<aprox; i++){
		for (j=0; j<aprox; j++){
			printf("%0.9f ", Laprox[i][j]);
		}
		printf("\n"); 
	}
	
	 
}



int main(){
	clock_t start = clock(); 
	int cantIntervalos = 2;
	int n = 1;
	double a = 0.0, b = PI; 
	
	
	extraRichardson(cantIntervalos, n, a, b, 0); 
		
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 
	return 0; 
}
