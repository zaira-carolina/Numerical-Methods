**USO UBUNTU, LINUX, DEBIAN**

1) Para ejecutar el archivo es necesario descargar la librería Cairo con el comando

	sudo apt-get install libcairo2-dev

1.1) En dado caso de no contar con un compilador, es necesario instalar g++:

	sudo apt install g++

2) El programa necesita de la carpeta de Fparser, por lo que se debe ejecutar desde la carpeta  donde está ubicada con los archivos presentes. 

3) El programa se ejecuta de la siguiente manera: 

	$ g++ graficadora.cpp $(pkg-config --libs --cflags cairo) fpoptimizer.cc fparser.cc
	
4) Se generará un archivo a.out, y este se ejecuta:

	$ ./a.out 
	
5) Aparecerá en consola un f(x) donde se ingresa la función deseada, por ejemplo:
	
	f(x) = sin(10*x)
	Inserte el valor de a:
	-4
	Inserte el valor de b:
	9 
6) Se generará un archivo en la carpeta llamado:
	"grafica.svg"

