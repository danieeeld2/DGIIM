#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Ejercicio 7 Repaso 1-5

if (( $# != 3 ));then
	echo "Faltan parámetros. Debes pasarle como argumentos un directorio, una letra y una palabra";
	exit 1
fi

if [[ -e $1 ]];then
	echo "Existe el directorio"
else
	mkdir $1;
	echo "Se ha creado $1"
fi

if [[ $2 != "f" && $2 != "d" ]];then
	echo "El segundo argumento debe ser una f o una d";
	exit 1
fi

touch salida;
(find $1 -name *$3*) > salida;
(find $1 -type $2) >> salida
 
exit
