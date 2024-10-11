// Método Iterativo de Jacobi 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include "funciones.h"
#define PI 3.141592654



void save_matriz(double **matriz, int N, char nombre_archivo[30]){
    FILE *outfile; 
    outfile = fopen(nombre_archivo, "w"); 
    int i, j; 
    for (i=0; i<N; i++){
        for (j=0; j<N; j++){
            fprintf(outfile, " %f ", matriz[i][j]); 
        }
        fprintf(outfile, "%s", "\n"); 
    }
}

void save_vector(double **matriz, int N, char nombre_archivo[30]){
    FILE *outfile;
    outfile = fopen(nombre_archivo, "w");
    int i; 
    for (i=0; i<N; i++){
        fprintf(outfile, "%f\n", matriz[i][i]); 
    }
}

double **matriz_tridiagonal(double valor_a, double valor_b, int N){
    double **matriz_tridiagonal; 
    double *alpha, *beta; 

    matriz_tridiagonal = matriz_vacia(N, N);
    alpha = vector_vacio(N, valor_a);  //valor diagonal
    beta = vector_vacio(N, valor_b); //valor al lado de la diagonal principal

    for (int i = 0; i<=N-1; i++){
        *(*(matriz_tridiagonal + i) + i) = *(alpha+i); 
        if ((i+1) < N){
            *(*(matriz_tridiagonal + i + 1)+i) = *(beta + i);
            *(*(matriz_tridiagonal + i) + i+1) = *(beta + i); 
        }  
    }
    return matriz_tridiagonal; 
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



//Encontrar el maximo fuera de la diagonal
void maximo(int N, double **a, int *imax, int *jmax){
    //generar los inicializadores de forma aleatoria 
    
    srand(time(0));
    int n1, n2; 
    n1 = rand() % N;
    n2 = rand() % N;
    
    while(n1==n2){
        n2 = rand () % N;
    }
    
    printf("\nInicializadores: %i y %i", n1, n2); 
    
    int i=n1, j=n2; 
    
    //int i = 1, j = 2; 
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

void metodo_jacobi_eigenvalores(double **a, int N, int cantidad_iteraciones){
    double **I, **eigenvectores; 
    eigenvectores = identidad(N); 
    int n, i, j, l, m; 
    int imax, jmax; 
    
    
    for (n=0; n<cantidad_iteraciones; n++){
        printf("\n n: %i \n", n); 
 
        maximo(N, a, &imax, &jmax); 
        I = identidad(N); 

        double num, den, theta; 
        num = 2*(*((*a+imax)+jmax));
        den =  (*(*(a+imax)+imax)) - (*(*(a+jmax)+jmax));

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

        I[imax][imax] = cos(theta);
        I[jmax][jmax] = cos(theta); 
        I[imax][jmax] = -sin(theta);
        I[jmax][imax] = sin(theta); 

        //a[imax][jmax] = 0.0; 
        eigenvectores = matmul(eigenvectores, I, N);
        }


        printf("\n A \n");
        for (i=0; i<N; i++){
            printf("\n Eigenvalor: %f ", a[i][i]);
        }
        printf("\n"); 


        printf("\n Matriz eigenvectores \n");
        imprimir_matriz(eigenvectores, N); 
        printf("\n"); 
        
        save_matriz(eigenvectores, N, "matriz_eigenvectores_v1.txt"); 
        save_vector(a, N, "eigenvalores.txt"); 
        

    }



int main(){
    clock_t start = clock();
    
    int N = 1000; 
	double **a; 
    a = matriz_tridiagonal(2.0, -1.0, N); //read_matriz(3, "matriz_ejemplo.txt"); 

    printf("\nMatriz A \n");
    imprimir_matriz(a, N);
    printf("\n"); 
    
    metodo_jacobi_eigenvalores(a, N, 100); 
    
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    printf("\nSegundos: %f", seconds); 
}