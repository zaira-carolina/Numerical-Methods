#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include "splines_funciones.h"

void splineRecta(double a, double b, int size, double x[], double y[]){
	double h; 
	int i, j; 
	int sizeIntervalo = 100;
	double X[size][sizeIntervalo], Y[size][sizeIntervalo]; 
	// GUARDAR PARA GRAFICAR
	saveArray(x, y, size, "splines0_n50_v15.txt"); 
		
		
	// Calcula la ecuación de la recta, y hacer una malla de puntos para graficarlos. 
	for (i=0; i<size; i++){
		h = fabs(x[i]-x[i+1])/sizeIntervalo;
		for (j=0; j<sizeIntervalo; j++){
			X[i][j] = x[i] + h*j;
			Y[i][j] = EcuacionRecta(X[i][j], x[i], y[i], x[i+1], y[i+1], size); 
		}
	}
		
	/*** GUARDAR DATOS PARA GRAFICAR ****/
	save_matriz(X, size, sizeIntervalo, "xsplines0_v15.txt");
	save_matriz(Y, size, sizeIntervalo, "ysplines0_v15.txt");
}

void SplineParabola(int size, double x[], double y[]){
	int i, j; 
	
	int N = size; // Cantidad de datos 
	int M = (size-1)*3; //(N-1)*2 + (N-2) + 1; 
	
	/**************   ARMAR LA MATRIZ  **********************************/
	double **matriz; 
	matriz = (double**)malloc(M*sizeof(double*));
	for (i=0; i<M; i++){
		matriz[i] = (double*)malloc(M*sizeof(double)); 
	}
 
	int count = 0, bcount = 0, bbcount = 0; 
	for (i=0; i<M; i++){
		if ((i%3) == 0){
			matriz[i-count][i] = 1.0;
			matriz[i-count+1][i+1] = x[count+1]-x[count]; 
			matriz[i-count+1][i+2] = (x[count+1]-x[count])*(x[count+1]-x[count]);
			count++; 
		}
	
		if (i >= (N-1)*2 && i<(M-1)){
			matriz[i][bcount+1] = 1.0; 
			matriz[i][bcount+2] = 2*(x[bbcount+1]-x[bbcount]);
			matriz[i][bcount+4] = -1.0; 
			bcount += 3; 
			bbcount ++; 
		}
	}
	matriz[M-1][2] = 1.0; 
	
	/************* ARMAR B ********************************************/
	double *b; 
	b = (double*)malloc(M*sizeof(double));
	int countb = 0, countbb = 0; 
	for (i = 0; i<M; i++){
		if (i<(N-1)*2){
			if (i%2 == 0){
				b[i] = y[countb]; 
				countb ++;
			}
			else{
				b[i] = y[countbb+1]-y[countbb]; 
				countbb++; 
			}
		}
	}
	
	//imprimir_matriz(matriz, M, M); 
	/****************** RESOLVER **************************************/
	/**CON LU DIO NAN**/
	double **Q, **QT, **R, *xsol, *ysol; 
	Q = matriz_vacia(M, M); 
	R = matriz_vacia(M, M);
	QR_matrix(matriz, Q, R, M); 
	
	QT = matriz_transpuesta(Q, M, M); 
	ysol = matriz_vector(QT, b, M); 
	xsol = triangular_superior_to_x(R, M, ysol);
	
	
	//for (i=0; i<M; i++){
	//	printf("\n i: %i, %f", i, xsol[i]); 
	//}
	
	/****************** GUARDAR TODO *********************************/
	saveArray(x, y, size, "xspline1_v15.txt");
	save_vector(xsol, M, "xsol_spline1_v15.txt"); 
}


void SplineCubico(int size, double x[], double y[]){
	int i, j; 
	/************************* ARMAR MATRIZ **************************/
	int M = size; 
	double **matriz; 
	matriz = (double**)malloc(M*sizeof(double*));
	for (i=0; i<M; i++){
		matriz[i] = (double*)malloc(M*sizeof(double)); 
	}
	matriz[0][0] = 1.0;
	matriz[M-1][M-1] = 1.0; 
	
	// Armar la matriz tridiagonal
	for (i=1; i<size-1; i++){
		matriz[i][i] = 2*(x[i+1]-x[i-1]); 
		matriz[i][i-1] = x[i]-x[i-1];
		matriz[i][i+1] = x[i+1]-x[i]; 
	}
	
	//imprimir_matriz(matriz, size, size); 
	/************* ARMAR B ********************************************/
	double *b; 
	b = (double*)malloc(M*sizeof(double));
	int countb = 0, countbb = 0; 
	b[0] = 0; 
	b[M-1] = 0; 
	for (i = 1; i<(M-1); i++){
		b[i] = 3*((y[i+1]-y[i])/(x[i+1]-x[i]) - (y[i]-y[i-1])/(x[i]-x[i-1])); // + ();
	}
	
	/************* FACTORIZAR Y RESOLVER ****************************/
	double **Q, **QT, **R, *coefC, *ysol; 
	Q = matriz_vacia(M, M); 
	R = matriz_vacia(M, M);
	QR_matrix(matriz, Q, R, M); 
	
	QT = matriz_transpuesta(Q, M, M); 
	ysol = matriz_vector(QT, b, M); 
	coefC = triangular_superior_to_x(R, M, ysol);

	/********OBTENER LOS OTROS COEFICIENTES ****************************/
	double *coefa, *coefb, *coefd; 
	coefa = (double*)malloc(sizeof(double)*size);
	coefb = (double*)malloc(sizeof(double)*size);
	coefd = (double*)malloc(sizeof(double)*size); 

	for (i=0; i<size; i++){
		coefa[i] = y[i]; 
		coefd[i] = (coefC[i+1]-coefC[i])/(3*(x[i+1]-x[i]));
		coefb[i] = (y[i+1]-y[i])/(x[i+1]-x[i])-(x[i+1]-x[i])*(2*coefC[i]+coefC[i+1])/3;
	}
	/********************** IMPRIMIR COEFICIENTES **********************/
	//for (i=0; i<M; i++){
	//	printf("\n a: %f, b: %f, c: %f, d: %f", coefa[i], coefb[i], coefC[i], coefd[i]); 
	//}
	saveArray(x, y, size, "splines3_n10_v15.txt"); 
	saveArray4(coefa, coefb, coefC, coefd, M, "spline3_n10_coef_v15.txt"); 
}

int main(){
	clock_t start = clock(); 
	
	int size = 30;
	double x[size], y[size], *pendiente;
	double a = -20.0, b = 20.0; 
	arrRandom(x, size, a, b);  
	sortArray(x, size); 
	int i, j;
	for (i=0; i<size; i++){
		y[i] = funx(x[i]);
	}
	
	// Intervalo
	splineRecta(a, b, size, x, y); 
	SplineParabola(size, x, y);
	SplineCubico(size, x, y);  

	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds);
    printf("\n"); 
}
