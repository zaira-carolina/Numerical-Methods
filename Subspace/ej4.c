#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include "funciones_iteracion.h"
#define PI 3.141592654

void matrix_copy_col(int N, double **matrix1,int col1, double **matrix2, int col2){
    for (int i=0; i<N; i++){
        matrix2[i][col2] = matrix1[i][col1]; 
    }
}


double **matrix_div(int N, double **matrix1, int col, double num){
    for (int i=0; i<N;i++){
        matrix1[i][col] = matrix1[i][col]/num;
    }
    return matrix1; 
}

double cols_mult(int N, double **matrix1, int col1, double **matrix2, int col2){
    double res = 0;
    for (int i=0; i<N; i++){
        res += matrix1[i][col1]*matrix2[i][col2];
    }
    return res; 
}

double *triangular_inferior_to_x(double **array, int N, double *b){
    double *x;
    x = (double*)malloc(N * sizeof(double)); 
    
    for (int i=0; i<N; i++){
        *(x+i) = 0.0; 
    }


    x[0] = b[0]/array[0][0]; 
    for (int i=1; i<N; i++){
        double suma = 0;
        for (int j=0; j<N; j++){
            if (i!=j){
                suma += array[i][j]*x[j]; 
            }
        x[i] = (*(b+i)-suma)/array[i][i];
        }
    }
    return x; 
}

double *triangular_superior_to_x(double **array, int N, double *b){
    double *x;
    x = (double*)malloc(N * sizeof(double*)); 
    for (int i=0; i<N; i++){
        *(x+i) = 0.0; 
    }

    x[N-1] = b[N-1]/array[N-1][N-1]; 
    for (int i=N-2; i>=0; i--){
        double suma = 0;
        for (int j=i+1; j<=N-1; j++){
            if (j>i){
                suma += *(*(array+i)+j)*(*(x + j)); 
            }
        *(x+i) = (*(b+i)-suma)/(*(*(array+i)+i));
        }
    }
    return x; 
}



void QR_matrix(double **A, double **Q, double **R, int N){
    int i, j, k; 
    for (i=0; i<N; i++){
        matrix_copy_col(N, A, i, Q, i); 
        for (j=0; j<i; j++){
            R[j][i] = cols_mult(N, Q, j, A, i);

            for (k=0; k<N; k++){
                Q[k][i] = Q[k][i]-R[j][i]*Q[k][j]; 
            }
        }
        
        R[i][i] = sqrt(cols_mult(N, Q, i, Q, i)); 
        for (int k=0; k<N; k++){
            Q[k][i] = Q[k][i]/R[i][i]; 
        }
    } 
}

void save_vector(double *vec, int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f\n", vec[i]); 
		}
}




int main(){
	//Tiempo
	
	clock_t start = clock(); 


    //Leer la matriz y vector 
    int filas, cols;
    int bfilas, bcols; 
    
    FILE *mat_file, *vec_file; 
    mat_file = fopen("M_sys_3x3.txt", "r");
    fscanf(mat_file, "%d%d\n", &filas, &cols);
    double **A;
    A = (double**)malloc(filas * sizeof(double*)); 
    for (int i=0; i<filas; i++){
        A[i] = (double*)malloc(cols * sizeof(double)); 
    }
    for(int i = 0; i < filas; i++){
	    for(int j = 0; j < cols; j++){
	        fscanf(mat_file, "%lf", &A[i][j]);
	    }
	}
    
    
    double *b; 
    vec_file = fopen("V_sys_3x1.txt", "r"); 
    fscanf(vec_file, "%d%d\n", &bfilas, &bcols);
    b = (double*)malloc(bfilas * sizeof(double*)); 
	for(int j = 0; j < bfilas; j++){
	    fscanf(vec_file, "%lf", &b[j]);
	}
	
	// Resolviendo sistema 
	double **Q, **R;
	Q = matriz_vacia(filas, cols);
    R = matriz_vacia(filas, cols);
    QR_matrix(A, Q, R, filas);
	double *x, *y; 
	double **QT; 
	QT = matriz_transpuesta(Q, filas, cols); 
	y = matriz_vector(QT, b, filas); 
	x = triangular_superior_to_x(R, filas, y);
	save_vector(x, filas, "x_3x3_qr.txt"); 

	
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds); 
	
    
	

    
    
	return 0; 
}
