#include <iostream>
#include <math.h>
#include <cmath>
#include "lib_metodos.h"
#include <ctime> 


unsigned t0, t1;
using namespace std;


int main(){
	t0=clock();

	/*TODO ES PARA EL USUARIO*/
	int metodo, cant_raices, No;
	cout << "Si quieres cambiar de función, accede a la paquetería lib_fun.h y ahí están las funciones listas" << endl; 


	cout << "Bisección : 1, Newton-Rapson: 2, ambos: 3" << endl;
	cin >> metodo; 
	
	double res_bis, res_newton;  
			
	cout << "¿Cuántas raíces va a buscar? " << endl; 
	cin >> cant_raices; 
	
	cout << "Cantidad de iteraciones: " << endl;
	cin >> No; 
		
	
	for (int i=1; i<= cant_raices; ++i){
		if (metodo == 1 || metodo == 3){
			double a, b; 
			
			cout << "Escriba a y b (separados por espacios) para la raíz " << i << " :" << endl; 
			cin >> a >> b; 
				
			res_bis = biseccion(a, b, pow(10, -10), No);
			cout << "Bisección: " << res_bis << endl;
				
			}
		
		if (metodo == 2 || metodo == 3){
			double po;

			cout << "Aproximación inicial raíz " << i << " :" << endl;
			cin >> po; 
			
			
			res_newton = newton_rapson(po, pow(10, -10), No); 
			cout << "Newton-Rapson: " << res_newton << endl; 
			}
		}
	t1 = clock();
	 
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout << "Tiempo: " << time << endl;	
return 0; 
}
