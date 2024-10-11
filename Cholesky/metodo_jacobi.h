double *jacobi(int No, int N, double **array, double *b, double valor){
    int iter = 0; 
    double num = 0, den = 0, TOL;  

    //VECTORES VACIOS
    double *VV, *VN;
    VV = (double*)malloc(N * sizeof(double*)); 
    VN = (double*)malloc(N * sizeof(double*)); 

    // Inicilizar el primer vector 
    for (int i=0; i<N; i++){
        *(VV+i) = (*(b+i))/(*(*(array+i)+i)); 
    }


    while (iter < No){

            for (int i=0; i<N; i++){
                double suma = 0; 
                for (int j=0; j<N; j++){
                    if (i!=j){
                        suma += (*(*(array+i)+j))*(*(VV+j)); 
                    }
                *(VN+i) = (*(b+i)-suma)/(*(*(array+i)+i)); 
                }
            num += (*(VN+i)-*(VV+i))*(*(VN+i)-*(VV+i)); 
            den += (*(VN+i))*(*(VN+i));
            }

            //printf("\n %f %f ", num, den); 
            TOL = num/den; 
            //printf("\n tol: %f", TOL); 
            if (TOL < valor) break; 
            else{
                for (int i=0; i<N; i++){
                    *(VV+i) = *(VN + i); 
                }
            }
            iter += 1; 
    }
    return VN; 
}