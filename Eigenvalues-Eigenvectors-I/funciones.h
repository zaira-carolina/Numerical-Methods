// solo hay que factorizar una vez
double **LL_factorizacion(double **L, int N, double *alpha, double *beta){
//double **L = matriz_vacia(N, N); 
    *(*L) = sqrt(*(alpha)); 
    for (int i = 0; i<N; i++){
            if ((i+1)<N){
            *(*(L + i + 1) + i) = (*(beta + i))/(*(*(L + i) + i));
            *(*(L + i + 1) + i+1) = sqrt(*(alpha + i + 1)-(*(*(L + i + 1) + i))*(*(*(L + i + 1) + i))); 
        }
    }
    return L; 
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

double *normalizar2(double *vector, int N){
    double suma = 0; 
    double *vector_nuevo;
	vector_nuevo = vector_vacio(N, 0.0); 
    
    
    for (int i=0; i<N; i++){
        suma += (*(vector+i))*(*(vector+i));
    }
    suma = sqrt(suma); 
    
    if (suma != 0){
        for (int i=0; i<N; i++){
            *(vector_nuevo+i) = *(vector+i)/(suma); 
        }    
    }
    return vector_nuevo; 
}

double *normalizar(double *vector, int N, double *suma){

    // Regresa el vector normalizado y la constante de normalización -> eigenvalor. 
    *suma = 0; 
    for (int i=0; i<N; i++){
        *suma += (*(vector+i))*(*(vector+i));
    }
    *suma = sqrt(*suma); 
    
    if (*suma != 0){
        for (int i=0; i<N; i++){
            *(vector+i) = *(vector+i)/(*suma); 
        }    
    }
    return vector; 
}

double vector_vector(double *vector1, double *vector2, int N){
    double suma = 0; 

    for (int i=0; i<N; i++){
        suma += (*(vector1+i))*(*(vector2+i));
    }
    return suma; 
}

double *matriz_vector(double **matriz, double *vector, int N){
    double *vector_resultante;
    vector_resultante = vector_vacio(N, 0.0); 

    for (int i=0; i<N; i++){
        double suma = 0;
        for (int j=0; j<N; j++){
            suma  += (*(*(matriz+j)+i))*(*(vector+j));
        }
    *(vector_resultante + i) = suma; 
    }
    return vector_resultante; 
}

