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

