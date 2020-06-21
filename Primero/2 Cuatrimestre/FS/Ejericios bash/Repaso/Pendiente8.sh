#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Dados 3 pará,etros, resuelve Ax^2+Bx+C

$resultado1=$((-1)*$2+($2**2-4*$1*$3)**(1/2));
$resultado2=$((-1)*$2-($2**2-4*$1*$3)**(1/2));
echo $resultado1 | bc -l;
echo $resultado2 | bc -l;
 
exit
