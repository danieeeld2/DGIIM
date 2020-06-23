#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Descripción en PDF de Repaso Práctica 1 a la 4

if (( $# != 2 ));then
	echo "El programa necesita dos argumentos, el primero un directorio
	y el segundo el nombre de un archivo"
else
	if [[ -f $2 ]];then
		touch salida;
		(cat $2 | head -3) > salida
	else
		echo "El segundo argumento no es un fichero "
	fi

	if [[ -d $1 ]];then
		ls $1 | wc -l
	else
		mkdir $1
	fi
	
	find $1 -readable >> salida;
	echo "De los `find $1 -type f | wc -l` archivos totales del directorio,
	hay `find $1 -readable | wc -l` archivos con permiso de lectura"
fi 
exit
