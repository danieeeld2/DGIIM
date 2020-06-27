#!/bin/bash
#Autor: Daniel Alconchel Vázuqez
#Descripción: Ejercicio 7 examen

uso="Guion que admita tres argumentos, el primero será un directorio, el segundo un comando y el tercero una palabra:\n 
examen-guion <nombre_directorio> <comando> <palabra>\n"

if (( $# != 3 ));then
	echo $uso;
	exit 1
fi

if [[ -d $1 ]];then
	echo "De los `find $1 -type f | wc -l` archivos del directorio, hay `find $1 -type f ! -executable | wc -l` que no son ejecutables"
else
	echo "El primer argumento no es un directorio"
fi

if [[ -n $2 ]];then
	(man $2 | head -10) > ayuda
	else
		echo "Segundo argumento vacío"
fi

if [[ -n $3 ]];then
	(more ayuda | grep -n $3 | cut -f1) > resultado
else
	echo "Tercer argumento vacío"
fi

exit
