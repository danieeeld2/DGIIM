#Escribe una script que realice los siguientes casos:
#1.Pide al usuario que introduzca una contraseña
#2.Pide al usario que repita la contraseña
#3.Si la contraseña no coincide con la inicial, muestra el mensaje El password no coincide, 
#inténtelo de nuevo
#4.Repite los pasos hasta que sea correcto

#!/bin/bash
# -*- ENCODING: UTF-8 -*-

continua=$true;
while $continua;
do
    read -p "Introduce una contraseña: " $var1;
    read -p "Introduzca la contraseña de nuevo: " $var2;
    if [ $var1 != $var2 ]
       then echo "El Password no coincide"
    else
      echo "El Password es correcto"; continua=$false
    fi
done

exit
