#define PI 3.141592654
double **matriz_vacia(int row, int col){
    double **array;
    array = (double**)malloc(row * sizeof(double*));
    for (int i = 0; i < row; i++) {
        array[i] = (double*)malloc(col * sizeof(double));
    }

    for(int i = 0; i <row; i++){
	    for(int j = 0; j <col; j++){
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

double **matriz_tridiagonal(double valor_a, double valor_b, int N){
    double **matriz_tridiagonal;  

    matriz_tridiagonal = matriz_vacia(N, N);

    for (int i = 0; i<=N-1; i++){
        *(*(matriz_tridiagonal + i) + i) = valor_a; 
        if ((i+1) < N){
            *(*(matriz_tridiagonal + i + 1)+i) = valor_b;
            *(*(matriz_tridiagonal + i) + i+1) = valor_b; 
        }  
    }
    return matriz_tridiagonal; 
}

void freeMatrix(double **matriz, int N){
    int i;
    for (i=0; i<N; i++){
        free(matriz[i]);
    }
    free(matriz); 
}

void imprimir_matriz(double **array, int N, int M){
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            printf("  %f  ", array[i][j]);
        }
        printf(" \n ");
    }
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
            suma  += matriz[i][j]*vector[j]; //(*(*(matriz+j)+i))*(*(vector+j));
        }
        vector_resultante[i] = suma;
    //*(vector_resultante + i) = suma; 
    }
    return vector_resultante; 
}

double *normalizar(double *vector, int N){
    double suma = 0; 
    for (int i=0; i<N; i++){
        suma += (*(vector+i))*(*(vector+i));
    }
    suma = sqrt(suma); 
    
    if (suma != 0){
        for (int i=0; i<N; i++){
            *(vector+i) = *(vector+i)/(suma); 
        }    
    }
    return vector;  
}

double **reducir_matriz(double **matriz, int filas, int cols){
    double **matriz_nueva; 
    int i, j; 
    matriz_nueva = matriz_vacia(filas, cols);
    for (i =0; i<filas; i++){
        for (j=0; j<cols; j++){
            matriz_nueva[i][j] = matriz[i][j];
        }
    }
    return matriz_nueva; 
}

double **potencia_eigen(int cant_eigenvalores, int N, double TOL, double **matriz){
        double **array, *v1, *v0; 
        array = matriz_vacia(N, N); 
        double constante; 
        
        for (int n=0; n<N; n++){ //ciclo para el número de eigenvalores a calcular

            v0 = vector_vacio(N, 0.2); 
            v0 = normalizar(v0, N); 
            v1 = vector_vacio(N, 0.0);
            
            double error = pow(10, 10); 
            double valor_viejo = 0.0,  valor_nuevo = 0 ; 

            while (error > TOL){

                for (int i=0; i<N; i++){
                    for (int k=0; k<n; k++){
                        v0[i] -= vector_vector(v0, array[k], N)*array[k][i];
                    }
                }
                
                
                for (int i=0; i<N; i++){
                    *(v1 + i) = *(matriz_vector(matriz, v0, N)+i); 
                }

                valor_nuevo = vector_vector(v0, v1, N);  
                error = fabs(valor_nuevo - valor_viejo); 
                v1 = normalizar(v1, N); 
                
                valor_viejo = valor_nuevo; 

                for (int i=0; i<N; i++){
                    *(v0+i) = *(v1+i); 
                    }
        
                }
                 
                for (int k=0; k<N; k++){
                    array[k][n] = v0[k]; 
                    //printf(" \n%f " ,v0[k]);
                    }
            
            //printf("\n Eigenvalor %f ", valor_nuevo); 
            } 

        if (N != cant_eigenvalores){
            double **new_array;
            //new_array = matriz_vacia(N, cant_eigenvalores);
            new_array = reducir_matriz(array, N, cant_eigenvalores);
            free(array); 
            return new_array;
        }



        free(v0); 
        free(v1);
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
    double suma, **result;
    result = matriz_vacia(filasA, colsB);  
    //#pragma omp parallel private(i, j, k)
    //#pragma omp parallel for
    for (i=0; i<filasA; i++){
        //Paralelizar con opem 
        for (j=0; j<colsB; j++){
            suma = 0; 
            for (k=0; k<colsA; k++){
                suma += A[i][k]*B[k][j];
            }
        result[i][j] = suma;         
        }
    }
    return result; //filas A, cols B 
} 

void maximo(int N, double **a, int *imax, int *jmax){
    //generar los inicializadores de forma aleatoria  
    
    int i = 1, j = 2; 
    double maximo;
    maximo = a[i][j]; 
    *imax = i; 
    *jmax = j; 

    for (i = 0; i<N; i++){
        for (j=0; j<N; j++){
            if (i!=j){
                if (fabs(a[i][j]) > fabs(maximo)){
                    maximo = a[i][j]; 
                    *imax = i; 
                    *jmax = j; 
                }
            }
        }
    }
}

double **identidad(int N){
    double **identidad;
    int i; 

    identidad = matriz_vacia(N, N); //ceros
    for (i=0; i<N; i++){
        identidad[i][i] = 1.0; 
    }
    return identidad; 
}

double **metodo_jacobi_eigenvalores(double **a, int N, int cantidad_iteraciones){
    int n, i, j, l, m; 
    int imax, jmax; 
    double **I, **eigenvectores;
    eigenvectores = identidad(N); 

        for (n=0; n<cantidad_iteraciones; n++){
            //printf("\n n: %i \n", n); 
    
            maximo(N, a, &imax, &jmax); 

            //printf("\n %f ", a[imax][jmax]); 
            if (fabs(a[imax][jmax]) < 0.000001){
                break; 
            } 
            double num, den, theta; 

            num = 2*a[imax][jmax]; 
            den = a[imax][imax]-a[jmax][jmax]; 

            if (a[imax][imax] == a[jmax][jmax]){
                if (a[imax][jmax] > 0){
                    theta = PI/4.0; 
                }
                else{
                    theta = (-1)*PI/4.0;
                }
            }
            else{
                theta = 0.5*atan2(num, den);
            }



            double b1, b2; 
            for (l = 0; l<N; l++){
                b1 = a[l][imax]*cos(theta)+a[l][jmax]*sin(theta);
                b2 = a[l][jmax]*cos(theta)-a[l][imax]*sin(theta);

                a[l][imax] = b1; 
                a[l][jmax] = b2;  
            }

            double c1, c2; 
            for (m = 0; m<N; m++){
                c1 = a[imax][m]*cos(theta) + a[jmax][m]*sin(theta);
                c2 = a[jmax][m]*cos(theta) - a[imax][m]*sin(theta); 

                a[imax][m] = c1;
                a[jmax][m] = c2;    
            }

            I = identidad(N); 
            I[imax][imax] = cos(theta);
            I[jmax][jmax] = cos(theta); 
            I[imax][jmax] = -sin(theta);
            I[jmax][imax] = sin(theta); 

            eigenvectores = matmul(eigenvectores, I, N, N, N);
            //Liberar matriz 
            int ii;
            for (ii=0; ii<N; ii++){
                free(I[ii]);
            }
            free(I); 
        }

        //for(i = 0; i<N; i++){
        //        printf("\n %f ", a[i][i]); 
        //    }
        //printf("\n"); 
    return eigenvectores; 
}

double **matriz_vacia2(int row, int col){
    double **array;
    array = (double**)malloc(row * sizeof(double*));
    for (int i = 0; i < row; i++) {
        array[i] = (double*)malloc(col * sizeof(double));
    }

    for(int i = 0; i <row; i++){
	    for(int j = 0; j <col; j++){
	        array[i][j] = 0.2;
	    }
	}
    return array; 
}

double **potencia_eigen2(int cant_eigenvalores, int N, double TOL, double **matriz, double **v0){
        double **array, *v1; 
        array = matriz_vacia(cant_eigenvalores,N); 
        
        for (int n=0; n<cant_eigenvalores; n++){ //ciclo para el número de eigenvalores a calcular

            //v0 = vector_vacio(N, 0.2); 
            v0[n] = normalizar(v0[n], N); 
            v1 = vector_vacio(N, 0.0);
            
            double error = pow(10, 10); 
            double valor_viejo = 0.0,  valor_nuevo = 0 ; 
            double constante;
                    
            while (error > TOL){

                for (int i=0; i<N; i++){
                    for (int k=0; k<n; k++){
                        v0[n][i] -= vector_vector(v0[n], array[k], N)*array[k][i];
                    }
                }
                
                
                for (int i=0; i<N; i++){
                    *(v1 + i) = *(matriz_vector(matriz, v0[n], N)+i); 
                }

                valor_nuevo = vector_vector(v0[n], v1, N);  
                error = fabs(valor_nuevo - valor_viejo); 
                v1 = normalizar(v1, N); 
                
                valor_viejo = valor_nuevo; 

                for (int i=0; i<N; i++){
                    v0[n][i] = *(v1+i); 
                    }
        
                }
                
                //printf("\n eigenvalor: %f \n", constante); 
                for (int k=0; k<N; k++){
                    array[n][k] = v0[n][k]; 
                    //printf(" \n%f " ,v0[k]);
                    }

            //for (int i=0; i<N; i++){
            //    for (int k=0; )
            //}

            
            //printf("\n Eigenvalor %f ", valor_nuevo);  
            //printf("\n Eigenvalor %f ", valor_nuevo); 
            }
        return array; 
}