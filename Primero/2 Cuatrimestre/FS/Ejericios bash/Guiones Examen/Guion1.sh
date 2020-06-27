#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Guión que recibe un único argumento. Si es un directorio, muestra el contenido del directorio y si es un fichero el contenido del mismo

if (( $# != 1 ));then
	echo "Error, debes pasarle un argumento. Este debe ser un fichero o un directorio";
	exit 1
fi

if [[ -d $1 ]];then
	ls $1
else
	if [[ -f $1 ]];then
		cat $1
	else
		echo "Debes pasarle un directorio o un fichero"
	fi
fi
 
exit
