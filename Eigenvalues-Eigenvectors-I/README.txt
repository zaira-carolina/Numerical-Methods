********* 11 de septiembre del 2022 ************
Para ejecutar los códigos es necesario escribir en consola:

gcc power_method.c

gcc inverse_power_method.c


Además, estos deben de estar en la carpeta que incluya el header
"funciones.h". 

************************************************
El archivo header "funciones.h" incluye las funciones matriciales
para hacer los métodos, como multiplicación de vectores, normas
y solución de sistemas de ecuaciones. 

En dado caso que no funcione, se debe de ejecutar usando '-lm' ya 
que para hacer la factorización de Cholesky (que se utiliza en el 
segundo método) se usa la función de sqrt de math.h. 