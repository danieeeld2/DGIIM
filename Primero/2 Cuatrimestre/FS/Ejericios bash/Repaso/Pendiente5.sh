#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Combinación ejercicio 3 y 4

touch modificado;
((grep -v "#" $1 && grep -v -e '^$' $1) | more) >> modificado; 
 
exit
