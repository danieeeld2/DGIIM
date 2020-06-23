#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Haciendo uso de las órdenes conocidas hasta el momento, construye un guión que admita dos parámetros, que compare por 
#separado si el primer parámetro que se le pasa es igual al segundo, o es menor, o es mayor, y que informe 
#tanto del valor de cada uno de los parámetros como del resultado de cada una de las evaluaciones mostrando un 0 o un 1, según corresponda.

echo "Los parámteros son $1 y $2 ";

if (( $1 == $2 ));then
	echo 0
else
	echo 1
fi

if (( $1 > $2 ));then
	echo 0
else
	echo 1
fi

if (( $1 < $2 ));then
	echo 0
else
	echo 1
fi


exit
