// Montecarlo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
double fun(double x, double y){
	return (x*x+y*y); 
}

double randNumber(double a, double b){
	double range = (b-a);
	double div = RAND_MAX/range;
	return (a + (rand() /div)); 
}

double FindMax(double x1, double x2, double y1, double y2,  int cantNumbers){
	double evalFun[cantNumbers];
	double hx = (x2-x1)/cantNumbers; 
	double hy = (y2-y1)/cantNumbers;
	
	double arrayx[cantNumbers];
	double arrayy[cantNumbers];
	
	for (int i=0; i<cantNumbers; i++){
		arrayx[i] = x1+i*hx; 
		arrayy[i] = y1+i*hy; 
	}
	
	for (int i=0; i<cantNumbers; i++){
		evalFun[i] = fun(arrayx[i], arrayy[i]); 
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

double FindMin(double x1, double x2, double y1, double y2,  int cantNumbers){
	double evalFun[cantNumbers];
	double hx = (x2-x1)/cantNumbers; 
	double hy = (y2-y1)/cantNumbers;
	
	double arrayx[cantNumbers];
	double arrayy[cantNumbers];
	
	for (int i=0; i<cantNumbers; i++){
		arrayx[i] = x1+i*hx; 
		arrayy[i] = y1+i*hy; 
	}
	
	for (int i=0; i<cantNumbers; i++){
		evalFun[i] = fun(arrayx[i], arrayy[i]); 
	}
	// Find max
	double min = evalFun[0]; 
	for (int i=0; i<cantNumbers; i++){
		if (evalFun[i] < min){
			min = evalFun[i];
		}
	}
	return min; 
}


double MonteCarlo(double x1, double x2, double y1, double y2, int cantNumbers, int cantNumbersIntegral){
	srand(time(NULL)); 
	
	double maxFun = FindMax(x1, x2, y1, y2, cantNumbers); 
	double minFun = FindMin(x1, x2, y1, y2, cantNumbers); 


	int count = 0; 
	for (int i=0; i<cantNumbersIntegral; i++){
		
		double pointx = randNumber(x1, x2);
		double pointy = randNumber(y1, y2);
		double pointz = randNumber(minFun, maxFun);
		double evalPoint = fun(pointx, pointy); 
		
		if (pointz <= evalPoint) count ++;
			
	}
	
	//printf("count: %i", count); 
	double vol = (x2-x1)*(y2-y1)*(maxFun-minFun); 
	double prop = (double)(count)/(double)(cantNumbersIntegral);
	return (vol*prop); 
}



int main(){

	clock_t start = clock(); 
	double res; 
	res = MonteCarlo(0, 1, 0, 1, 1000, 20000); 
	printf("\n res:%f", res); 
	
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 

}
