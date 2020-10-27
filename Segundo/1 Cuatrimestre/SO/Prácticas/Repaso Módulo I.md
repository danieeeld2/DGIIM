# Repaso Módulo I

###### Daniel Alconchel Vázquez

------

1. **Crear en el directorio /root un enlace duro y un enlace simbólico a  cualesquiera de los programa que aparecen en /bin. Una vez creados hacer un   ls -l del directorio /root y pegar el resultado. Idem para la oden  stat sobre estos dos archivos.**

   ```bash
   $ pwd
   /root
   $ ln /bin/ls /root/lshardlink
   $ ln -s /bin/ls /root/lssoftlink
   $ ls -l /root/
    7602856 -rwxr-xr-x 2 root root 142144 sep  5  2019 lshardlink
   17170457 lrwxrwxrwx 1 root root      7 oct 27 09:25 lssoftlink -> /bin/ls
   17170437 drwxr-xr-x 4 root root   4096 oct  1 11:02 snap
   
   # La l del principio del softlink nos indica que es un metadato y, por tanto, efectivamente es un softlink. Para ver que es un hardlink, simplemente ver que los inodos coinciden
   
   $ ls -li /bin/ls
   7602856 -rwxr-xr-x 2 root root 142144 sep  5  2019 /bin/ls
   
   $ stat /bin/ls
     Fichero: /bin/ls
     Tamaño: 142144    	Bloques: 280        Bloque E/S: 4096   fichero regular
   Dispositivo: 802h/2050d	Nodo-i: 7602856     Enlaces: 2
   Acceso: (0755/-rwxr-xr-x)  Uid: (    0/    root)   Gid: (    0/    root)
   Acceso: 2020-10-27 09:25:08.191717400 +0100
   Modificación: 2019-09-05 12:38:40.000000000 +0200
         Cambio: 2020-10-27 09:24:29.895215063 +0100
       Creación: -
   
   ####
   
   Como vemos el hardlink tiene el mismo inodo, mientras que el softlink tiene un inodo distinto
   ```

2. **Un bash shell restringido (bash -r) permite limitar algunas acciones del usuario que los usa, por ejemplo, no permite cambiar de directorio, ni utilizar nombres de archivos que contienen una barra /, ni cambiar las variables PATH y SHELL, ni redirigir las entradas/salidas, ni tampoco definir funciones. Se pide crear un usuario, denominado anonimo, que debe usar un shell restringido, tiene un UID con valor 590 y pertenecerá a un grupo denominado limitados con GID 1010.Su directorio homes será /home/anonimo y su cuenta debe estar activa solo 10 días.**

   ```bash
   $ groupadd limitados --gid 1010
   $ adduser anonimo
   $ vi /etc/passwd
   anonimo:x:590:1010::/home/anonimo:/bin/rbash
   
   ### También podemos
   $ adduser anonimo --uid 590 --shel /bin/rbash --home /home/anonimo --gid 1010
   
   ### Para la fecha de expiración
   $ chage -E 2020-11-06 anonimo
   
   ### También podemos
   $ at now + 10days 
   ```

3. **Crea un archivo llamado log en tu directorio home y consigue que todos los Viernes a las 2 horas y 5 minutos durante los meses de Marzo, Abril y Mayo, se ejecute el guión del apartado anterior y se guarden los resultados en el archivo creado ( log ), de tal forma que se pueda observar la evolución de la memoria. Para verificar que funciona pruébalo especificando "cada minuto". Crea un script que devuelva exclusivamente la información sobre la cantidad de espacio libre y ocupado tanto de la memoria principal como del espacio de intercambio de tu sistema (Ubuntu).**

   ```bash
   $ free
                total       used       free     shared    buffers     cached
   Mem:       1019240      40340     978900          0       3816      18428
   -/+ buffers/cache:      18096    1001144
   Swap:            0          0          0
   
   $ touch script.sh
   $ chmod +x script.sh
   $ vi script.sh
   #!/bin/bash
   
   free | formato >> log.txt 
   
   $ crontab -e
   5 2 * 3-5 5 /home/daniel/script.sh
   
   # Si no hacemos el cauce en el script
   5 2 * 3-5 5 /home/daniel/script.sh >> /home/daniel/log.txt
   ```

4. **Buscar los usuarios creados en un sistema y los grupos**

   ```bash
   $ cat /etc/passwd
   
   # Si quieres buscar una en concreto
   
   $ cat /etc/passwd | grep nombre
   
   # Para los grupos
   
   $ cat /etc/group | grep www-data
   ```

