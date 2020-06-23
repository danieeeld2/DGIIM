#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Dados 3 pará,etros, resuelve Ax^2+Bx+C

echo "Los resultados de la ecuación de segundo grado son: ";
$resultado1=$(-1*$2+sqrt($2*$2-4*$1*$3));
echo $resultado1 | bc -l

exit
