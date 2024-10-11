#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include "elemento_finito_funciones.h"

double Ni(double h, int k, double x, double z[]){
	// Ni
	double ni; 
	if (k > 0){
		if (x >= z[k-1] && x <= z[k]){
			ni = (1.0/h)*(x-z[k-1]);
			return ni; 
		}
	}
	if (x >= z[k] &&  x <= z[k+1]){
		ni = (1.0-(1.0/h)*(x-z[k]));
		return ni;
	}

	
	return 0; 
}

	
void elementoFinito(double x[], double y[], int cantIntervalos, int cantPuntos){			
	int i, j, k; 
	
	double a = x[0], b = x[cantPuntos-1];
	double h = (b-a)/cantIntervalos;
	double lambda = 0.0; 

	// Puntos en z; 
	double z[cantIntervalos+1];
	for (i=0; i<(cantIntervalos+1); i++){
		z[i] = a + h*i; 
	}
	
	// Para cada k tendre una submatriz
	double **matriz, *r; 
	matriz = (double**)malloc((cantIntervalos+1)*sizeof(double*));
	r = (double*)malloc((cantIntervalos+1)*sizeof(double)); 
	for (i=0; i<(cantIntervalos+1); i++){
		matriz[i] = (double*)malloc((cantIntervalos+1)*sizeof(double)); 
	}

	double suma00, suma11, suma01, s, rSuma; 
	
	for (k=0; k<(cantIntervalos+1); k++){
		suma00 = 0;
		suma01 = 0;
		suma11 = 0;
		s = 0; 
		rSuma = 0; 
		
		//printf("\n fila: %i", k); 
		if(k == 0){
			for (i=0; i<cantPuntos; i++){
				suma00 += Ni(h, k, x[i], z)*Ni(h, k, x[i], z); 
				suma01 += Ni(h, k+1, x[i], z)*Ni(h, k, x[i], z); 
				rSuma    += Ni(h, k, x[i], z)*y[i]; 
			}
			
			
			matriz[k][k]   = suma00 + lambda/h;
			matriz[k][k+1] = suma01 - lambda/h;
			r[k] = rSuma; 
			continue;
		}
		
		if(k == cantIntervalos){
			for (i=0; i<cantPuntos; i++){
				suma11 += Ni(h, k, x[i], z)*Ni(h, k, x[i], z); 
				suma01 += Ni(h, k, x[i], z)*Ni(h, k+1, x[i], z); 
				rSuma += Ni(h, k, x[i], z)*y[i]; 
			}
			matriz[k][k]   = suma11 + lambda/h;
			matriz[k][k-1] = suma01 - lambda/h;
			r[k] = rSuma; 
			continue;
		}
		
		for (i=0; i<cantPuntos; i++){
			suma00 += Ni(h, k, x[i], z)*Ni(h, k, x[i], z);   // ak
			suma01 += Ni(h, k-1, x[i], z)*Ni(h, k, x[i], z); // bk
			suma11 += Ni(h, k, x[i], z)*Ni(h, k, x[i], z);   // ck
			s      += Ni(h, k+1, x[i], z)*Ni(h, k, x[i], z); // bk+1
			rSuma+= Ni(h, k, x[i], z)*y[i]; 
		}
			
		matriz[k][k-1] = suma01 - lambda/h;
		matriz[k][k]   = suma11 + lambda/h + suma00 + lambda/h;
		matriz[k][k+1] = s - lambda/h;
		r[k] = rSuma + rSuma; 
		
	}
	
	double **Q, **QT, **R, *phi, *ysol;  
	int M = (cantIntervalos+1); 
	Q = matriz_vacia(M, M); 
	R = matriz_vacia(M, M);
	QR_matrix(matriz, Q, R, M); 
	
	QT = matriz_transpuesta(Q, M, M); 
	ysol = matriz_vector(QT, r, M); 
	phi = triangular_superior_to_x(R, M, ysol); 
	
	save_vector(phi, M, "sol_v10.txt"); 
}




int main(){
	
	clock_t start = clock(); 

	int cantIntervalos = 40;
	int cantPuntos = 100;

	double x[cantPuntos], y[cantPuntos]; 
	arrRandom(x, cantPuntos, -20, 20);
	sortArray(x, cantPuntos); 
	arrEval(y, x, cantPuntos); 
	saveArray(x, y, cantPuntos, "ej1_v10.txt"); 

	elementoFinito(x, y, cantIntervalos, cantPuntos); 

	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 
	
	return 0;
}
