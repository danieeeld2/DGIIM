#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Elimina las líneas en blanco de un archivo

touch archivomodificado;
(grep -v -e '^$' $1 | more) >> archivomodificado;
 
exit
