#!/bin/bash
#Autor: Daniel Alocnhel Vázquez 
#Descripción: Segunda parte del examen parcial 2019 

echo `find /etc -user "root" -perm -o+r -regex ".+/[^rpa]+$" -not -mtime -14` 

exit
