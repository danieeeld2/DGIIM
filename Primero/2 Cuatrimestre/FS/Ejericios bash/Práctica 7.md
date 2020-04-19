# Práctica 7

```bash
#!/bin/bash
# -*- ENCODING: UTF-8 -*-
#Título: Ejercicio 7
#Autor: Daniel Alconchel Vázquez
#Descripción: Ver enunciado en pdf de prado "Repaso Prácticas 1-5"

#Comprobamos los parámetros
if [ $# != 3 ];
	then echo "Error en los argumentos, debes pasar 3 argumentos, los cuales son nombre de 		un directorio, una letra y una palabra. Para ver que hace el guión mirar descripción"; 		exit
fi

#Comprobamos si existe el directorio

if [ -d "$1" ]
	then echo "El directorio ya existe"
else
	echo "Se ha creado el directorio $1"; mkdir $1
fi

#Comprobamos que el segundo argumento sea f o d

if [ "$2" != "f" ] && [ "$2" != "d" ]
	then echo "Error. El segundo parametro no es ni f ni d"; exit
fi

#Buscamos el tercer argumento dentro del directorio y almacenarlo en un fichero a parte el resultado

grep -rn "$3" */ >> ~/resultado;
#Buscar en el directorio todo los archivos del tipo $2

find . -type "$2" >> ~/resultado;

exit



```

