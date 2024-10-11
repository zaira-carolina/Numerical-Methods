// gradiente conjugado
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>



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

double vector_vector(double *vector1, double *vector2, int N){
    double suma = 0; 

    for (int i=0; i<N; i++){
        suma += (*(vector1+i))*(*(vector2+i));
    }
    return suma; 
}

double *vector_resta(int N, double *v1, double *v2){
    double *vres; 
    vres = vector_vacio(N, 0.0);
    for (int i=0; i<N; i++){
        vres[i] = v1[i]-v2[i]; 
    }
    return vres; 
}

double *x_grad_pre(double **A, double *b, int filas, int cols, double TOL){
		double **M_inversa;
		M_inversa = matriz_vacia(filas, filas); 
		for (int i=0; i<filas; i++){
			M_inversa[i][i] = 1/A[i][i]; 
		}
		
		double *xk, *x0; 
		x0 = vector_vacio(filas, 0.2);
		double *r, alpha; 
		int k = 0;
		
		double *y0, *p0; 
		double *coef; 
		coef = vector_vacio(filas, 0.0);
		
		double error; 
		error = 30;


		while (error >  TOL){
			r = vector_resta(filas, b, matriz_vector(A, x0, filas));
			y0 = matriz_vector(M_inversa, r, filas); 
			p0 = y0; 
			alpha = vector_vector(r, y0, filas)/(vector_vector(p0, matriz_vector(A, p0, filas), filas));
			for (int i=0; i<filas; i++){
				x0[i] = x0[i] + alpha*p0[i]; 
				coef[i] = alpha*(matriz_vector(A, p0, filas))[i]; 
				}
        
			r = vector_resta(filas, r, coef); 
			error = sqrt(vector_vector(r, r, filas)); 
			k = k+1; 
		}
		
		return x0; 
	}
	
void save_vector(double *vec, int N, char nombre[30]){
	FILE *outfile;
	outfile = fopen(nombre, "w"); 
	int i; 
	for (i=0; i<N; i++){
		fprintf(outfile, "%f\n", vec[i]); 
	}
}


int main(){
	
	//Tiempo
	
	clock_t start = clock(); 


    //Leer la matriz y vector 
    int filas, cols;
    int bfilas, bcols; 
    
    FILE *mat_file, *vec_file; 
    mat_file = fopen("M_sys_3x3.txt", "r");
    fscanf(mat_file, "%d%d\n", &filas, &cols);
    double **A;
    A = (double**)malloc(filas * sizeof(double*)); 
    for (int i=0; i<filas; i++){
        A[i] = (double*)malloc(cols * sizeof(double)); 
    }
    for(int i = 0; i < filas; i++){
	    for(int j = 0; j < cols; j++){
	        fscanf(mat_file, "%lf", &A[i][j]);
	    }
	}
    
    
    double *b; 
    vec_file = fopen("V_sys_3x1.txt", "r"); 
    fscanf(vec_file, "%d%d\n", &bfilas, &bcols);
    b = (double*)malloc(bfilas * sizeof(double*)); 
	for(int j = 0; j < bfilas; j++){
	    fscanf(vec_file, "%lf", &b[j]);
	}
	
	//Solucion
	double *x; 
	x = x_grad_pre(A, b, filas, cols, 0.0001); 
	//for (int i=0; i<filas; i++){
	//	printf("\n %f", x[i]); 
	//	}
		
	save_vector(x, filas, "x_grad_pre_3x3.txt"); 
		
	clock_t end = clock(); 
    float seconds = (float)(end-start)/CLOCKS_PER_SEC; 
    printf("\n Segundos: %f", seconds); 


    
}
