#!/bin/bash

#Comrpobamos el número de parámetros

if (( $# != 1 )); then
	echo Error en parámetros. Pasa 2 parámetros
fi

# Usamos la orden top, que trae todo lo pedido, -p es para pasarle un PID,
# -b para redireccionar y -n para el número de iteraciones, porque 
# recordemos que es una interfaz gráfica

top -p $1 -b -n 1 > top.txt # Redireccionamos la salida

exit

