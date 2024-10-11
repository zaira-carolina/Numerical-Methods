************** 16 octubre 2022 *******************
Para ejecutar el código:

gcc splines_tres_metodos.c -lm

*************SOBRE CÓDIGO ***********************
1) El archivo "spliens_funciones.h" contiene todas las funciones necesarias
excepto los métodos, estos están en el código "splines_tres_metodos.c"

2) El método "splineRecta" guarda una malla de puntos, para sólo graficar
las funciones.
Para cambiar el nombre de los pares de puntos: línea 18
para cambiar el nombre en la malla de puntos: línea 31, 32.

3) El método "SplineParabola" guarda los coeficientes de las parábolas entre puntos,
Para cambiar el nombre de los pares de puntos: línea 102, 
para cambiar el nombre de los coeficientes obtenidos: línea 103.

4) El método "SplineCubico" guarda los coeficientes de los polinomios cúbicos.
Para cambiar el nombre de los pares de puntos: línea 162, 
para cambiar el nombre d elos coeficientes: línea 163.

5) El archivo main tiene una variable llamada "size", y con 
"arrRandom" se generan size números en el rango a, b. 

