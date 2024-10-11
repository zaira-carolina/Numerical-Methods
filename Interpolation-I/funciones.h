
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



double **matrizMinimos(int degree, double datosX[]){
	int rows = degree+1; 
	
	double **array; 
	array = (double**)malloc(rows*sizeof(double*));
	for (int i=0; i<rows; i++){
		array[i] = (double*)malloc(rows*sizeof(double));
	}
	
	int i, j;
	for (i=0; i<rows; i++){
		array[i][0] = 1.0;
		for (j=0; j<rows; j++){
			array[i][j] = pow(datosX[i], j);
		}
	}
	return array; 
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

double **matmul(double **A, double **B, int filasA, int colsB, int colsA){
	int i, j, k; 
	double **prod; 
	prod = matriz_vacia(filasA, colsA); 
	
	for (i = 0; i<filasA; i++){
		for (j=0; j<colsB; j++){
			double suma = 0; 
			#pragma omp parallel for reduction (+:suma)
			for (k=0; k<colsA; k++){
				suma += A[i][k]*B[k][j];
			}
			prod[i][j] = suma;
		}
	}
	return prod; 
}

double *prod_matvec( double **A, double *B, int N){

    int i, j;
    double *V1 , sum;

    V1 = (double*)malloc(N*sizeof(double));

    for( i=0; i<N; i++){
        sum = 0;
        #pragma omp parallel for reduction(+:sum)
        for( j=0; j<N; j++) {
            sum += A[i][j]*B[j];
        }
        V1[i] = sum;
    }
    return V1;
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
                suma += array[i][j]*x[j]; //*(*(array+i)+j)*(*(x + j)); 
            }
        x[i] = (b[i]-suma)/array[i][i]; 
        //x[i] = (*(b+i)-suma)/array[i][i];
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



double **matrizMinimosFun(int degree, double datosX[]){
	int rows = degree+1; 
	
	double **array; 
	array = (double**)malloc(rows*sizeof(double*));
	for (int i=0; i<rows; i++){
		array[i] = (double*)malloc(rows*sizeof(double));
	}
	
	int i, j;
	for (i=0; i<rows; i++){
		array[i][0] = cos(pow(datosX[i], 0));
		//for (j=0; j<rows; j++){
		array[i][1] = sin(pow(datosX[i], 1));
		array[i][2] = cos(pow(datosX[i], 2)); 
		//}
	}
	return array; 
}
