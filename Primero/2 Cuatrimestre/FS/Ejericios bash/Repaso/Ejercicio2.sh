#!/bin/bash
#Título: pendrive
#Fecha: 20 de Junio 2020
#Autor: Daniel Alconchel
#Versión: 1.0
#Descripción: verifique si hay algún dispositivo pendrive conectado al computador

if [[ `lsusb` == "" ]]; 
then
    echo "No existe ningún dispositivo conectado"
else
    echo "Existe algún dispositivo conectado";
    lsusb    
fi;
