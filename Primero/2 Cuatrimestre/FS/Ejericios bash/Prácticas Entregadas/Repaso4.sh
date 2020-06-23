#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Guión de Repaso 4

#A partir del directorio personal y utilizando una única orden, cree un 
#directorio llamado repaso, 
#dentro de él otros dos directorios llamados prueba1y prueba2, 
#y dentro de prueba1 otro directorio llamado ejercicio1. 

cd ~; mkdir repaso -p repaso/prueba1/ejercicio1 repaso/prueba2;

#Situados en el directorio ejercicio1, con una única orden, 
#cree cinco archivos llamados arch1.txt, 
#arch2.txt, arch3.txt, arch4.pdfy arch5.pdf 

cd repaso/prueba1/ejercicio1/;
touch arch1.txt arch2.txt arch3.txt arch4.pdf arch5.pfd;

#Desde el directorio ejercicio1, redireccione al archivo arch1.txt 
#elresultado de buscar la palabra “expresiones” en 
#la ayuda (help) de la ordenlet

(help let | more)>arch1.txt;

#Desde  el directorio  personal,  
#copie  los  ficheros  de  ejercicio1  cuya  
#extensión  tenga  una  x  al directorio prueba2.

cd ~;
cp repaso/prueba1/ejercicio1/*.*x* repaso/prueba2/;

#Nuevamente desde el directorio personal, 
#obtenga las 15 primeras líneas del manual de la orden find 
#y añádalo al final del archivo arch1.txt del directorioprueba2. 

((man find | head -15) | more) >> repaso/prueba1/ejercicio1/arch1.txt;

exit

