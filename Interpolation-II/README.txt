*************** 30 OCTUBRE 2022 *****************
Para ejecutar cualquier archivo:

gcc newton-cotes.c -lm

gcc richardson-extrapolation.c -lm

gcc rombert-method.c -lm 

*********** SOBRE LOS MÉTODOS *******************

newton-cotes.c : 
- Para cambiar la función a integrar: línea 8
- Para cambiar los límites de integración: línea 73, valor a, valor b. 
- Para ver el cambio con los subintervalos: línea 71
- Para cambiar el método: línea 72
Este programa está para un polinomio de grado 1 hasta uno de grado 6. 

richardson-extrapolation.c :
- Para cambiar la función a integrar: línea 11
- Para cambiar los límites: línea 114
Se muestra la matriz hasta h**4.

rombert-method.c : 
- Para cambiar la función a integrar: línea 11
- Para cambiar los límites de integración: línea 117
Se muestra la matriz hasta h**4. 
