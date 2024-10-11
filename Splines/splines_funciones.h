#define SIZE 50
#define SIZECOLS 100

void saveArray(double x[], double y[], int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f %f\n", x[i], y[i]); 
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


double **matriz_vacia(int row, int col){
	double **array; 
	array = (double**)malloc(row*sizeof(double*));
	for (int i=0; i<row; i++){
		array[i] = (double *)malloc(col*sizeof(double));
	}
	
	for (int i=0; i<row; i++){
		for (int j = 0; j<col; j++){
			array[i][j] = 0.0; 
			}
	}
	return array;
}


double *vector_vacio(int N, double valor_inicial){
    double *arreglo;
    arreglo = (double*)malloc(N * sizeof(double*)); 

    for(int i = 0; i < N; i++){
	    arreglo[i] = valor_inicial;
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


double *triangular_inferior_to_x(double **array, int N, double *b){
    double *x;
    x = (double*)malloc(N * sizeof(double)); 
    
    for (int i=0; i<N; i++){
        x[i] = 0.0; 
    }


    x[0] = b[0]/array[0][0]; 
    for (int i=1; i<N; i++){
        double suma = 0;
        for (int j=0; j<N; j++){
            if (i!=j){
                suma += array[i][j]*x[j]; 
            }
        x[i] = (b[i]-suma)/array[i][i];
        }
    }
    return x; 
}

double *triangular_superior_to_x(double **array, int N, double *b){
    double *x;
    x = (double*)malloc(N * sizeof(double*)); 
    for (int i=0; i<N; i++){
        x[i] = 0.0; 
    }

    x[N-1] = b[N-1]/array[N-1][N-1]; 
    for (int i=N-2; i>=0; i--){
        double suma = 0;
        for (int j=i+1; j<=N-1; j++){
            if (j>i){
                suma += array[i][j]*x[j]; 
            }
        x[i] = (b[i]-suma)/array[i][i];
        }
    }
    return x; 
}

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
    #pragma omp parallel for reduction (+:res)
    for (int i=0; i<N; i++){
        res += matrix1[i][col1]*matrix2[i][col2];
    }
    return res; 
}

    
void QR_matrix(double **A, double **Q, double **R, int N){
    int i, j, k; 
    for (i=0; i<N; i++){
		//printf("\n%i ", i); 
        matrix_copy_col(N, A, i, Q, i); 
        for (j=0; j<i; j++){
            R[j][i] = cols_mult(N, Q, j, A, i);

            for (k=0; k<N; k++){
                Q[k][i] = Q[k][i]-R[j][i]*Q[k][j]; 
            }
        }
        
        R[i][i] = sqrt(cols_mult(N, Q, i, Q, i)); 
        #pragma omp parallel for 
        for (int k=0; k<N; k++){
            Q[k][i] = Q[k][i]/R[i][i]; 
        }
    } 
}

double **matriz_transpuesta(double **array, int filasA, int colsA){
    double **arreglo;
    arreglo = (double**)malloc(colsA * sizeof(double*)); 
    for (int i=0; i<colsA; i++){
        arreglo[i] = (double*)malloc(filasA * sizeof(double)); 
    }

    for(int i = 0; i < colsA; i++){
	    for(int j = 0; j <filasA; j++){
	        arreglo[i][j] = array[j][i];
	    }
	}
    return arreglo; 
}


double *matriz_vector(double **matriz, double *vector, int N){
    double *vector_resultante;
    vector_resultante = vector_vacio(N, 0.0); 

    for (int i=0; i<N; i++){
        double suma = 0;
        #pragma omp parallel for reduction (+:suma)
        for (int j=0; j<N; j++){
            suma  += matriz[i][j]*vector[j]; 
        }
        vector_resultante[i] = suma; 
    }
    return vector_resultante; 
}

double funx(double x){
	return x + (x*sin(x/2))/3;
}

void arrEval(double y[], double x[], int size){
	int i;
	for (i=0; i<size; i++){
		y[i] = funx(x[i]); 
	}
}

double randfrom(double min, double max){
	//srand(time(0)); 
	double range = (max-min); 
	double div = RAND_MAX/range; 
	return min+(rand()/div); 
}

void arrRandom(double array[], int size, double min, double max){
	int i; 
	for (i=0; i<size; i++){
		array[i] = randfrom(min, max); 
	}
}

double EcuacionRecta(double xrecta, double x1, double y1, double x2, double y2, int size){
	int i;
	double pendiente, yrecta;
	pendiente = (y2-y1)/(x2-x1);
	yrecta = pendiente*(xrecta-x1)+y1; 
	return yrecta; 
}

void save_matriz(double matriz[SIZE][SIZECOLS], int filas, int cols, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i, j; 
	for (i=0; i<filas; i++){
		for (j=0; j<cols; j++){
			fprintf(outfile, "%f ", matriz[i][j]);
		}
		fprintf(outfile, "\n");
	}
}


void sortArray(double x[], int size){
	int i, j;
	double temp; 
	for (i=0; i<size; i++){
		for (j=i+1; j<size; j++){
			if (x[i]>x[j]){
				temp = x[i];
				x[i] = x[j];
				x[j] = temp; 
			}
		}
	}
}

void saveArray4(double a[], double b[], double c[], double d[], int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f %f %f %f\n", a[i], b[i], c[i], d[i]); 
	}
}


void imprimir_matriz(double **array, int N, int M){
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            printf("%f ", array[i][j]);
        }
        printf(" \n ");
    }
}
