## Ejercicio Pŕactica 7

###### Daniel Alconchel Vázquez

------

#### Ejercicio 1

*Considerando los ficheros proporcionados ( main2.cpp, factorial.cpp, hello.cpp, sin.cpp, cos.cpp y*
*tan.cpp ), realiza las siguientes operaciones por pasos (no te saltes ninguno y ve mostrando cada uno*
*de los resultados requeridos):*

1. *Escribe en un archivo makefile las órdenes necesarias para que dé la posibilidad de crear el*
*archivo compilado **hello.o**.*
*a. Mediante el makefile, haz que se cree dicho fichero.*
2. *Modifica el mismo archivo para se puedan compilar los archivos **tan.cpp, cos.cpp y sin.cpp** y*
*obtener sus correspondientes archivos objeto.*
*a. Mediante el makefile, haz que se creen cada uno de los ficheros independientemente.*
*b. Mediante el makefile, haz que se creen cada uno de los ficheros de 1 sola vez.*
3. *Seguidamente, modifica el makefile para que genere una librería llamada **libmath**.*
*a. Ejecuta el makefile y comprueba qué resultado ha proporcionado.*
4. *Añade las órdenes necesarias para obtener el programa principal compilado y un **fichero***
***ejecutable denominado** Practica7.*

**Ejercicio 1.1**

Archivo makefile

```bash
# Archivo Makefile Ejercicio1.1
# Uso: make -f makefile1.1
hello.o: hello.cpp
	g++ -c hello.cpp
```

![Sin nombre](/home/daniel/Imágenes/Sin nombre.png)

Ahora usamos el archivo makefile

```bash
make -f makefile1.1
```

![Captura de pantalla de 2020-05a-15 19-13-49](/home/daniel/Imágenes/Captura de pantalla de 2020-05a-15 19-13-49.png)

**Ejercicio 1.2.a**

Archivo makefile

```bash
# Archivo makefile Ejercicio1.2
# Uso: make -f makefile1.2 hello.o | tan.o | cos.o | sin.o

hello.o: hello.cpp
	g++ -c hello.cpp
	
tan.o: tan.cpp
	g++ -c tan.cpp

cos.o: cos.cpp
	g++ -c cos.cpp
	
sin.o: sin.cpp
	g++ -c sin.cpp

```

![Captura de pantalla de 20210-05-15 19-18-58](/home/daniel/Imágenes/Captura de pantalla de 20210-05-15 19-18-58.png)

Ejecución de makefile

hello.o

```bash
make -f makefile.2 hello.o
```

tan.o

```bash
make -f makefile.2 tan.o
```

cos.o

```bash
make -f makefile.2 cos.o
```

sin.o

```bash
make -f makefile.2 sin.o
```

**Ejercicio 1.2.b**

![Captura de pantalla de 2020-05-15 191-28-46](/home/daniel/Imágenes/Captura de pantalla de 2020-05-15 191-28-46.png)



![Captura de pantalla de 2020-05-152 19-31-36](/home/daniel/Imágenes/Captura de pantalla de 2020-05-152 19-31-36.png)

**Ejercicio 1.3**

![Captura de pantalla de 2020-05-15 19-324-22](/home/daniel/Imágenes/Captura de pantalla de 2020-05-15 19-324-22.png)



![Captura de pantalla de 202110-05-15 19-38-37](/home/daniel/Imágenes/Captura de pantalla de 202110-05-15 19-38-37.png)

**Ejercicio 1.4**

![Captura de pantalla de 202000-05-15 19-42-25](/home/daniel/Imágenes/Captura de pantalla de 202000-05-15 19-42-25.png)



![Captura de pantalla de 20a20-05-15 19-49-07](/home/daniel/Imágenes/Captura de pantalla de 20a20-05-15 19-49-07.png)



#### Ejercicio 2

*Haciendo uso del archivo anterior, genera un nuevo makefile añadiendo al código las*
*siguientes variables:*

1. *Una variable que almacene dónde están los ficheros **include.***
2. *Una variable que almacene el **compilador**.*
3. *Utiliza la variable en la que se guarda el **nombre del objetivo** de la regla actual para*
*no tener que repetir siempre dicha cadena.*
4. *Modifica las reglas que puedas utilizando la variable donde se almacenan las*
***dependencias** de la regla actual.*



**Ejercicio 2.1**

![Captura de pantalla de 202000-05-15 19-42-25](/home/daniel/Imágenes/Captura de pantalla de 202000-05-15 19-42-25.png)



![Captura de pantalla de 2020-05-15 19-56668-31](/home/daniel/Imágenes/Captura de pantalla de 2020-05-15 19-56668-31.png)



**Ejercicio 2.2**

![Captura de pantalla de 2020-05-15 20-0111-34](/home/daniel/Imágenes/Captura de pantalla de 2020-05-15 20-0111-34.png)



![Captura de pantalla de 2020-05-152222 20-07-34](/home/daniel/Imágenes/Captura de pantalla de 2020-05-152222 20-07-34.png)



**Ejercicio 2.3**

![Captura de pantalla de 2020-05-1555 20-13-53](/home/daniel/Imágenes/Captura de pantalla de 2020-05-1555 20-13-53.png)



![Captura de pantalla de 202110-05-15 20-18-03](/home/daniel/Imágenes/Captura de pantalla de 202110-05-15 20-18-03.png)



**Ejercicio 2.4**

![Captura de pantalla de 2020-05-15 20º2-20-32](/home/daniel/Imágenes/Captura de pantalla de 2020-05-15 20º2-20-32.png)



![Captura de pantalla deee 2020-05-15 20-25-15](/home/daniel/Imágenes/Captura de pantalla deee 2020-05-15 20-25-15.png)