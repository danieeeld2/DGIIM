#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Práctica3. Guión que muestra los archivos de un directorio que le pasamos como primer argumento y que han sido accedidos en los últimos x días, segundo argumento

echo "Los archivos del directorio $1 que han sido modificado en los últimos $2 días son: ";
find $1 -atime -$2


 
exit
