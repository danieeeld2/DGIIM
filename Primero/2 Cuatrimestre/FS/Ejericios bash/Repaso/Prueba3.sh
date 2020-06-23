#!/bin/bash
#Autor: Daniel Alconchel Vázquez 
#Descripción: Señala las palabras en rojo que contengan la secuencia de letras ea y me de todos los 
#archivos terminados en .sh en el directorio que se ejecuta en el guión 

grep -n --color=always "[e][a]\[m][e]" *.sh

exit
