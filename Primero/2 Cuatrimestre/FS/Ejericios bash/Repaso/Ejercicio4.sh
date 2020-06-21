#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Programa que elimina las líneas de comentarios de una script

touch archivomodificado.sh;
(grep -v "#" $1 | more) > archivomodificado.sh;
exit 
