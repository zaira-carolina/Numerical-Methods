void imprimir_matriz(double **array, int N){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            printf("  %f  ", array[i][j]);
        }
        printf(" \n ");
    }
}

double *vector_vacio(int N, double valor_inicial){
    double *arreglo;
    arreglo = (double*)malloc(N * sizeof(double*)); 

    for(int i = 0; i < N; i++){
	    arreglo[i] = valor_inicial;
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

// Funcion para multiplicar matrices
double **matmul(double **A, double **B, int N){
    int i, j, k; 
    double suma, **result;
    result = matriz_vacia(N, N);  

    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            suma = 0; 
            for (k=0; k<N; k++){
                suma += (*(*(A+i)+k))*(*(*(B+k)+j));
            }
        (*(*(result+i)+j)) = suma;         
        }
    }
    return result; 
} 