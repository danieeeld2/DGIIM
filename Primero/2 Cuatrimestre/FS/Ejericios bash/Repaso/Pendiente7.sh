#!/bin/bash
#Autor: Daniel Alconchel Vázquez 
#Descripción: Indica cuando fué la última vez que se conecto el usuario que ejecutó 
# esta script

lastlog | grep -v $USER;
 
exit
