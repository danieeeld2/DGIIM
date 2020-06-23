#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Práctica 2

#Listar el contenido del directorio /etc/ a un archivo de nombre ejercicio1
ls /etc > ~/ejercicio1

#Añadir la ruta actual al  archivo de ejercicio1
pwd >> ~/ejercicio1

#Busca si existe el archivo sample.txt en /root/
(ls sample.txt && echo "file found") || echo "file not found"

exit
