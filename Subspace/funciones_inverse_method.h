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

void freeMatrix(double **matriz, int N){
    int i;
    for (i=0; i<N; i++){
        free(matriz[i]);
    }
    free(matriz); 
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


//metodo Cholesky
double **L_Cholesky(double **array, int N){

    // Crear memoria dinámica para la matriz
    double **L;
    L = (double**)malloc(N * sizeof(double*)); 
    for (int i=0; i<N; i++){
        L[i] = (double*)malloc(N * sizeof(double)); 
    }

    // Inicializarla en cero
    for(int i = 0; i < N; i++){
	    for(int j = 0; j < N; j++){
	        L[i][j] = 0.0;
	    }
	}

    //Codigo Cholesky
    *(*L) = sqrt(*(*array)); 
    for (int j=1; j<N; j++){
        *(*(L+j)) = *(*(array+j))/(*(*L));
		for (int i=1; i<=j; i++){
			double suma = 0;  
			if (i!=j){
				for (int k=0; k<=i-1; k++){
					suma += (*(*(L+j)+k))*(*(*(L+i)+k));
					}
                *(*(L+j)+i) = (*(*(array+j)+i)-suma)/(*(*(L+i)+i)); 
			}
            else{
				for (int k=0; k<=i-1; k++){
                    suma += (*(*(L+i)+k))*(*(*(L+i)+k)); 
				}
                (*(*(L+i)+i)) = sqrt( (*(*(array+i)+i)) - suma ); 
			}
		}
	}

    return L; 
    
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


void imprimir_matriz(double **array, int N, int M){
    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            printf("  %f  ", array[i][j]);
        }
        printf(" \n ");
    }
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

double *vector_vacio(int N, double valor_inicial){
    double *arreglo;
    arreglo = (double*)malloc(N * sizeof(double*)); 

    for(int i = 0; i < N; i++){
	    arreglo[i] = valor_inicial;
	}
    return arreglo; 
}

double vector_vector(double *vector1, double *vector2, int N){
    double suma = 0; 

    for (int i=0; i<N; i++){
        suma += (*(vector1+i))*(*(vector2+i));
    }
    return suma; 
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

double **eigenvalor_chico(int cant_eigenvalores, double **L, double **U, int N, double TOL, double **v0){

    double **array;
    array = matriz_vacia(cant_eigenvalores,N);
    
    int i, j; 
    double *v1; 

    for (int n = 0; n<cant_eigenvalores; n++){
        //printf("\n n: %i", n); 

        //double *v0, *v1; 
        //v0 = vector_vacio(N, 1.0); 
        v0[n] = normalizar(v0[n], N); 
        v1 = vector_vacio(N, 0.0);
        double lambda, lambda_old = pow(10, 20);
        double valor = 1.0; 
        
        while (fabs(valor)>TOL){
            
            for (int i=0; i<N; i++){
                    for (int k=0; k<n; k++){
                        v0[n][i] -= vector_vector(v0[n], array[k], N)*array[k][i];
                    }
                }


            v1 = triangular_superior_to_x(U, N, triangular_inferior_to_x(L, N, v0[n])); 
            double suma = 0; 
            for (i=0; i<N; i++){
                suma += v0[n][i]*v1[i];
            }
            lambda = (1/suma); 
            valor = fabs(lambda-lambda_old); 
            v1 = normalizar(v1, N);

            for (i=0; i<N; i++){
                v0[n][i] = v1[i];
            }
            lambda_old = lambda; 
        }
    printf("\n Eigenvalor %i : %f", n,  lambda); 

    for (int k=0; k<N; k++){
		array[n][k] = v0[n][k]; 
	    }
    
    }
    //free(b)
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