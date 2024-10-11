// Montecarlo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#define SEED 35791246
double fun(double x){
	return (x*x + 2*x+5); 
}

double randNumber(double a, double b){
	double range = (b-a);
	double div = RAND_MAX/range;
	return (a + (rand() /div)); 
}

double FindMax(double a, double b, int cantNumbers){
	double evalFun[cantNumbers];
	
	double h = (b-a)/cantNumbers; 
	double array[cantNumbers];
	
	for (int i=0; i<cantNumbers; i++){
		array[i] = a+i*h; 
	}
	
	for (int i=0; i<cantNumbers; i++){
		evalFun[i] = fun(array[i]); 
	}
	// Find max
	double max = evalFun[0]; 
	for (int i=0; i<cantNumbers; i++){
		if (evalFun[i] > max){
			max = evalFun[i];
		}
	}
	return max; 
}

double FindMin(double a, double b, int cantNumbers){
	double evalFun[cantNumbers];
	
	double h = (b-a)/cantNumbers; 
	double array[cantNumbers];
	
	for (int i=0; i<cantNumbers; i++){
		array[i] = a+i*h; 
	}
	for (int i=0; i<cantNumbers; i++){
		evalFun[i] = fun(array[i]); 
	}
	// Find min
	double min = evalFun[0];
	for (int i=0; i<cantNumbers; i++){
		if (evalFun[i] < min){
			min = evalFun[i];
		}
	}
	return min;
}


double MonteCarlo(double a, double b, int cantNumbers, int cantNumbersIntegral){
	srand(time(NULL)); 
	// Encontrar el maximo
	double maxFun = FindMax(a, b, cantNumbers); 
	double minFun = FindMin(a, b, cantNumbers); 
	double area = (b-a)*(maxFun-minFun); 
	
	
	printf("\n max: %f, min: %f", maxFun, minFun); 
	int count = 0; 
	// Generar puntos y ver si estan dentro
	for (int i=0; i<cantNumbersIntegral; i++){
		double pointx = randNumber(a, b);
		double pointy = randNumber(minFun, maxFun);
		double evalPoint = fun(pointx); 
		//printf("\n pointx: %f, pointy: %f, evalPoint: %f", pointx, pointy, evalPoint); 
		
		if (pointy <= evalPoint) count ++;
		//else { 
		//	count --;	
		//}
	}
	
	//printf("\n count: %i, cantNumberIntegral: %i", count, cantNumbersIntegral); 
	double prop = (double)(count)/(double)(cantNumbersIntegral);
	//printf("prop: %f", fabs(prop)); 
	double integral = prop*area + minFun*(b-a);
	return fabs(integral); 
	//return count; 
}



int main(){
	clock_t start = clock(); 

	double res; 
	res = MonteCarlo(0, 3, 1000, 200000); 
	printf("\n res:%f", res); 
	printf("\n"); 
	
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 

}
