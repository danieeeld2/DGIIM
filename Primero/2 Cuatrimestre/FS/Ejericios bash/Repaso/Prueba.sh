#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Prueba A 2019

ayuda="\n Los modos de uso de examen1.sh son:\n
 1-> ./examen1.sh cadenaCaracteres. Saca todos los archivos del directorio \n
	 de trabajo que contenga en su nombre la cadenaCaracteres, ó \n
 2-> ./examen1.sh  nombreArchivo1 nombreArchivo2. Si no existe el archivo nombreArchivo2, \n copia el archivo nombreArchivo1 en el archivo nombreArchivo2. Si ya existe el archivo \n nombreArchivo2, entonces se le añade al final del archivo nombreArchivo2 el contenido del \n archivo nombrearchivo1, ó \n
 3-> ./examen1.sh  nombrearchivo1 nombreDirectorio. Copia el archivo nombreArchivo1 \n 
en el directorio nombreDirectorio.  ó	\n 
 4->d. En cualquier otro caso que sea ejecutado el guión ./examen1.sh, Deberá imprimir \n
 sobre el terminal el texto que contiene los apartados (a) hasta el (d), que servirá de ayuda.
\n "

#Saca todos los archivos del directorio de trabajo
if [[ $1 == "a" ]];then
	ls -d *$2*
fi

#Si no existe el Archivo2, copia el archivo 2 en 1, sino se escribe el contenido al final
if [[ $1 == "b" ]]; then
	if [[ -e $2 ]];then
		if [[ -e $3 ]];then
			more $2 >> $3;
			echo "Se ha actualizado el archivo"
		else
			touch $3;
        		cp $2 $3;
        		echo "Se ha copiado el archivo"
		fi
	else
		echo "No existe el archivo a copiar"
	fi
fi

#Copia el archivo nobreArchivo1 en nombreDirectorio
if [[ $1 == "c" ]];then
	if [[ -e $2 ]]; then
		cp $2 $3;
		echo "Se ha copiado el archivo en el directorio"
	else
		echo "No existe el archivo"
	fi
fi

#Ejecuta la excepción
if [[ $1 != "a" && $1 != "b" && $1 != "c" ]];then
	echo -e "\n Error en el uso del programa";
	echo -e $ayuda
fi

exit
