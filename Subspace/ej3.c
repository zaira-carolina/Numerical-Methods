#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 

double **matriz_vacia(int N, int M){
    double **arreglo;
    arreglo = (double**)malloc(N * sizeof(double*)); 
    for (int i=0; i<N; i++){
        arreglo[i] = (double*)malloc(M * sizeof(double)); 
    }

    for(int i = 0; i < N; i++){
	    for(int j = 0; j < N; j++){
	        arreglo[i][j] = 0.0;
	    }
	}
    return arreglo; 
}

double *read_b(int N, char name_file[20]){
    FILE *file; 
    file = fopen(name_file, "r"); 
    
    double *arreglo;
    arreglo = (double*)malloc(N * sizeof(double*)); 

	for(int j = 0; j < N; j++){
	    fscanf(file, "%lf", &arreglo[j]);
	}
    return arreglo; 
}

void LU_matrix(double **A, double **L, double **U, int filas, int cols){
    int i, j, k; 
    
    for (i = 0; i<filas; i++){
        for (k=i; k<cols; k++){
            double suma = 0; 
            for (j=0; j<i; j++){
                suma +=(L[i][j])*(U[j][k]); 
            }
            U[i][k] = A[i][k]-suma; 
        }

        for (k=i; k<cols; k++){
            if (i==k){
                L[i][i] = 1.0; 
            }
            else{
                double suma = 0; 
                for (j=0; j<i; j++){
                    suma += L[k][j]*U[j][i]; 
                }
                L[k][i] = (A[k][i]-suma)/U[i][i]; 
            }
        }
    }
}

void imprimir_matriz(double **array, int N){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf(" %f ", array[i][j]);
        }
        printf("\n");
    }
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
                suma += array[i][j]*x[j]; //*(*(array+i)+j)*(*(x + j)); 
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

double vector_vector(double *vector1, double *vector2, int N){
    double suma = 0; 

    for (int i=0; i<N; i++){
        suma += (*(vector1+i))*(*(vector2+i));
    }
    return suma; 
}

double *vector_vacio(int N, double valor_inicial){
    double *arreglo;
    arreglo = (double*)malloc(N * sizeof(double*)); 

    for(int i = 0; i < N; i++){
	    arreglo[i] = valor_inicial;
	}
    return arreglo; 
}

double *matriz_vector(double **matriz, double *vector, int N){
    double *vector_resultante;
    vector_resultante = vector_vacio(N, 0.0); 

    for (int i=0; i<N; i++){
        double suma = 0;
        for (int j=0; j<N; j++){
            suma  += matriz[i][j]*vector[j]; //(*(*(matriz+j)+i))*(*(vector+j));
        }
        vector_resultante[i] = suma;
    //*(vector_resultante + i) = suma; 
    }
    return vector_resultante; 
}

double *vector_resta(int N, double *v1, double *v2){
    double *vres; 
    vres = vector_vacio(N, 0.0);
    for (int i=0; i<N; i++){
        vres[i] = v1[i]-v2[i]; 
    }
    return vres; 
}

double coef_ray(double **A, double *b, int N, double TOL){
		
		double **L, **U; 
		L = matriz_vacia(N, N);
		U = matriz_vacia(N, N);
		LU_matrix(A, L, U, N, N);

		double *x; 
		double sigma, error, *vres; 
		error = 30;

		while (error > TOL){
			x = triangular_superior_to_x(U, N, triangular_inferior_to_x(L, N, b));
			sigma = vector_vector(x, matriz_vector(A, x, N), N)/(vector_vector(x, x, N));
			for (int i=0; i<N; i++){
				x[i] = sigma*x[i]; 
			}
			vres = vector_resta(N, b, x); 
			error = sqrt(vector_vector(vres, vres, N));

			for (int i=0; i<N; i++){
				b[i] = x[i]; 
			}
		}
		return sigma; 
	}

int main(){
	//Tiempo
	clock_t start = clock(); 

    //Leer la matriz
    int filas, cols; 
    FILE *mat_file; 
    mat_file = fopen("Eigen_3x3.txt", "r");
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
	b = vector_vacio(filas, 1.0); 
	double sigma; 
	sigma = coef_ray(A, b, filas, 0.01);  
	printf(" %f ", sigma); 
	


	
	return 0; 
}
