#include "lib_fun.h"
#include <iostream>

using namespace std; 


double funcion_derivada(double x){
	double h, derivadax; 
	
	h = pow(10, -5); 
	derivadax = (funcion(x+h)-funcion(x))/h; 
	
	return derivadax; 
	}

double biseccion(double a, double b, double TOL, int No){
    double p, FA, FB, FP;
    p = 0; 
    int i = 1;
    while (i <= No){
		p = (b+a)/2; 
		FA = funcion(a);
		FP = funcion(p);  
		if (FP == 0 || (b-a)/2 < TOL){
			break; 
			}
		else{
			i += 1; 
			if (FA*FP > 0)
				a = p; 
			else 
				b = p; 
			} 
		}
	return p;
	}	

    
double newton_rapson(double po, double TOL, int No){
	double p;
	int i = 1; 
	
	while (i<= No){
		p = po -funcion(po)/funcion_derivada(po); 
		if (abs(p-po) < TOL){
			break; 
			}
		i += 1; 
		po = p; 
		}
	return p; 
	}
