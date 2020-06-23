#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Calculadora

seguir=$true;
while $seguir
do
	echo "Introduce dos números: ";
	read V1;
	read V2;
	echo "Introduzca una opción: ";
	read Opcion;

	echo $V1;
	echo $V2;
	
	if [[ $Opcion -eq "1" ]];then
		expr $V1 + $V2
	fi
	if [[ $Opcion -eq "2" ]];then
		expr $V1 - $V2
	fi
	if [[ $Opcion -eq "3" ]];then
		expr $V1 * $V2
	fi
	if [[ $Opcion -eq "4" ]];then
		exit 1;
		$seguir=$false
	fi
done
exit
