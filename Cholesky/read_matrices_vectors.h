double **read_matriz(int N, char name_file[20]){
    FILE *file; 
    file = fopen(name_file, "rb"); 
    
    double **arreglo;
    arreglo = (double**)malloc(N * sizeof(double*)); 
    for (int i=0; i<N; i++){
        arreglo[i] = (double*)malloc(N * sizeof(double)); 
    }

    for(int i = 0; i < N; i++){
	    for(int j = 0; j < N; j++){
	        fscanf(file, "%lf", &arreglo[i][j]);
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

double *vector_vacio(int N, double valor_inicial){
    double *arreglo;
    arreglo = (double*)malloc(N * sizeof(double*)); 

    for(int i = 0; i < N; i++){
	    arreglo[i] = valor_inicial;
	}
    return arreglo; 
}


void imprimir_matriz(double **array, int N){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf(" %i ", array[i][j]);
        }
        printf("\n");
    }
}

void imprimir_matriz2(double **array, int N){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf("  %f  ", array[i][j]);
        }
        printf(" \n ");
    }
}

double **matriz_transpuesta(double **array, int N){
    double **arreglo;
    arreglo = (double**)malloc(N * sizeof(double*)); 
    for (int i=0; i<N; i++){
        arreglo[i] = (double*)malloc(N * sizeof(double)); 
    }

    for(int i = 0; i < N; i++){
	    for(int j = 0; j < N; j++){
	        arreglo[i][j] = array[j][i];
	    }
	}
    return arreglo; 
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
