#!/bin/bash
#Autor: Daniel Alconchel Vázquez
#Descripción: Script que crea automáticamente una script de bash, con los permisos modificados

touch $1;
echo "#!/bin/bash" > $1;
echo "#Autor: " >> $1;
echo "#Descripción: " >> $1;
echo " " >> $1;
echo "exit" >> $1;
chmod +x $1;
exit
