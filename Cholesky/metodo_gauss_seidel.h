double *gauss(int No, int N, double **array, double *b){
    int iter = 0; 
    double num = 0, den = 0, TOL;  

    //VECTORES VACIOS
    double *VN; 
    VN = (double*)malloc(N * sizeof(double*)); 

    // Inicilizar el primer vector 
    for (int i=0; i<N; i++){
        *(VN+i) = 1.0; 
    }
    while (iter < No){
        for (int i=0; i<N; i++){
            double suma = 0;
            for (int j=0; j<N; j++){
                if (i!=j){
                    suma += (*(*(array+i)+j))*(*(VN+j)); 
                }
            }
            *(VN + i) = (*(b+i)-suma)/(*(*(array+i)+i)); 
        }
    iter += 1;
    }
    return VN; 
}