#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Elimina comentarios y espacios en blanco

touch salida.sh;
(cat $1 | grep -ve '^[#]\|^$') > salida.sh

exit
