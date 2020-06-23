#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Crea un guión que tenga dos argumentos de tipo numérico. Si alguno de los argumentos no es un número finaliza y 
#muestra un mensaje al usuario del error "el argumento .... no es un numero". A continuación, compara ambos 
#argumentos. Si son iguales, crea una variable con los nombres de los archivos del directorio actual del usuario y si 
#son distintos crea una variable con los nombres de los archivos del directorio home del usuario. 
#Finalmente imprime en pantalla el contenido de dicha variable y el nombre de ruta del directorio (actual o home, según sea el caso).

es_numero='^-?[0-9]+([.][0-9]+)?$';
if [[ $1=~$es_numero && $2=~$es_numero ]]; then
	if [[ $1 -eq $2 ]];then
		caso1=`ls .`
	else
		caso2=`ls ~`
	fi
else
	echo "El argumento no es un número"
fi

exit
