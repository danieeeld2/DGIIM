#!/bin/bash
#Autor: Daniel Alconchel Vázuqez
#Descripción: Repaso 5

#Cree tres directorios con una única orden: 
#curso_1920y dentro de éste, cuatrimestre_1y cuatrimestre_2.
 
mkdir curso_1920 -p curso_1920/cuatrimestre_1 curso_1920/cuatrimestre_2;

#Creeun  archivo  cuyo  nombre  sea repasoMod1en  el  
#directorio curso_1920.    A continuación, edíteloy escriba lo siguiente: 
#DNI: número del DNI
#Nombre y apellidos: nombre y apellidos
#Fecha: fecha actual (dd/mm/aaaa)

cd curso_1920/;
touch repasoMod1;
echo "DNI: número del DNI" >> repasoMod1;
echo "Nombre y apellidos: nombre y apellidos " >> repasoMod1;
echo "	Fecha: fecha actual (dd/mm/aaaa)" >> repasoMod1;

#Copie el archivo repasoMod1del directorio curso_1920 
#en el directorio cuatrimestre_1

cd ..;
cp curso_1920/repasoMod1 curso_1920/cuatrimestre_1/;

#Redireccione el resultado de ejecutar la orden que obtiene la 
#fecha actual al fichero que ha creado en el punto 2 
#(en el directorio curso_1920) sin destruir su contenido.

stat -c %y curso_1920/repasoMod1;

#Indique qué es necesario hacer para crear una variable RUTA 
#que contenga la ruta absoluta del  directorio  en  el  que  nos  encontramos.  #Compruebe  con  el  comando  correspondiente  
#las variables locales de su sistema.

ruta=$pwd;
echo $ruta;

#Obtenga  las  20  últimas  líneas  del  manual  de  la  
#orden  find  y  guárdelas  en  un  fichero llamado ayudafind, 
#dentro del directorio cuatrimestre_2

touch curso_1920/cuatrimestre_2/ayudafind;
(man find | tail -20) > curso_1920/cuatrimestre_2/ayudafind

exit
