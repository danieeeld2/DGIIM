# PRÁCTICA SISTEMAS OPERATIVOS

###### DANIEL ALCONCHEL VÁZQUEZ

------

Convertirse en administrador del sistema implica entrar al mismo como usuario **root**.

```bash
$ whoami	# pido a la shell el nombre del usuario actual
Daniel

$su			# solicito el cambio de usuario a modo root
Password:	# el sistema solicita la contraseña de root

$ whoami	# suele  cambiar el prompt del sistema
root
```



### 4.2 Usuarios

Un usuario es una "persona" que trabaja en el sistema mediante una cuenta de usuario. En Linux, se caracteriza por disponer de:

- Nombre de usuario (*username*)

- Un identificador de usuario (**UID**), que es un número entero que le asigna el sistema, internamente, a cada usuario y que lo representa.

- El grupo o grupos a los que pertenece (**GID**). Todo usuario tiene asignado un **grupo principal**, que aparece en el archivo ***/etc/psswd***, pero puede pertenecer a más de un grupo, loscuales se llaman **grupos suplementarios**, que se encuentra en ***/etc/group***.

  

##### 4.2.1 Creación de cuentas

Para añadir un usuario al sistema se realizan los siguientes pasos:

1. Decidir el nombre de usuario y los grupos a los que va a pertenecer
2. Introducir los datos en los archivos */etc/passwd* y */etc/group*
3. Asignar un password a la nueva cuenta
4. Establecer parámetros de envejecimiento
5. Crear directorio de inicio del nuevo usuario */home*
6. Copiar los archivos de inicialización (.bash_profile, .bashrc,...)
7. Establecer otras facilidades: quotas, mail, permisos para imprimir, etc.
8. Ejecutar cualquier tarea de inicialización propia del sistema.
9. Probar la nueva cuenta



Para crear nuevas cuentas utilizaremos las siguientes órdenes, las cuales se encargan de todo, a excepción del paso 7:

```bash
$ useradd

$ adduser
```

Se   creará   el   usuario   y   su   grupo   principal,   así   como   las   entradas   correspondientes   en/etc/passwd,  /etc/shadow  y  /etc/group.   También   se   creará   el   directorio   de   inicio,normalmente en /home, y los archivos de configuración particulares para cada usuario que seubican dentro de este directorio y que se detallan más adelante. 



Probemos a crear un usuario, para ello:

```bash
$useradd nombreusuario #En mi caso usaré Pablo
$vi /etc/passwd
root::0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
...
Pablo:x:500:500::/home/Pablo:/bin/bash
$vi /etc/group
root:x:0:root
bin:x:1:root,bin,daemon
...
Pablo:x:500:

```



Disponemos también de algunas órdenes para gestión de cuentas de usuario:

| Órdenes             | Función                                                      |
| ------------------- | ------------------------------------------------------------ |
| usermod             | Modifica una cuenta ya existente                             |
| userdel             | Elimina una cuenta de usuario (Por defecto no elimina Home)  |
| newusers            | Crea cuentas de usuario utilizando datos de un archivo de texto, que ha de tener el formato de */etc/passwd* |
| system-config-users | Herramienta modo gráfico                                     |

En el directorio **/etc/skel** se guardan los archivos de configuración del shell, los cuales se copian en el HOME del usuario para su uso. Dependen de los siguientes intérpretes de orden:



| .bash_profile    | Se ejecuta al hacer login y en él podremos indicar alias, variables, etc... que deseamos al inicio de la sesión |
| ---------------- | ------------------------------------------------------------ |
| **.bashrc**      | **Se ejecuta cada vez que se ejecuta una shell**             |
| **.bash_logout** | **Se ejecuta al salir del usuario del sistema y le podremos indicar acciones que deseamos ejecutar al salir del sistema** |



Hagamos un pequeño ejercicio. Creemos tres usuarios:

```bash
$ useradd Ximo
$ useradd Pablo
$ useradd Alejandro

# Esto ha creado tres usuarios. Probemos a eliminar uno

$ userdel Ximo

# Esto provia que desaparezca de los archivos /etc/group /etc/passwd ..., pero su carpeta home localicada en /home sigue existiendo
```



Podemos asignar o cambiar las contraseñas de los usuarios mediante la siguiente orden:

```bash
$ passwd <nombreusuario>
```

Si se ejecuta la orden con un usuario normal, este solo podrá cambiar su contraseña, pero si se ejecuta como administrador del sistema, se podrá cambiar las contraseñas de todos los usuraios.



También, podemos cambiar la shell de un usuario mediante la orden **chsh**. Todas las shells permitidas se encuentran en el archivo ***/etc/shells***. Si se desea que el usuario no pueda entrar al sistema se le puede asignar al campo de la shell el archivo ***/bin/false*** o ***/sbin/nologin***.



Como hemos comentado anteriormente,  podemos establecer restricciones de envejecimiento que se guardan en el archivo ***/etc/shadow***. Estos son los valores posibles:

| Ordenes  | Descripción                                                  |
| -------- | ------------------------------------------------------------ |
| minfile  | Número de días que han de pasar para poder cambiar la contraseña |
| maxlife  | Número de días máximo que puede estar con la misma contraseña sin cambiarla |
| warn     | Cuántos días antes de la que contraseña expire (**maxfile**) será informado sobre ello, indicándole que tiene que cambiarla |
| inactive | Número de días después de que la contraseña de que la contraseña expire que la cuenta se deshabilitará de forma automática si no ha sido cambiada |
| expired  | Fecha en la que la cuenta expira y se deshabilita de forma automática |
| changed  | Fecha del último cambio de contraseña                        |



Los valores los establece el administrador con las órdenes **change** o con **passwd**. Recordemos que el archivo **/etc/login.defs** tiene los valores por defecto.

Veamos ahora algunas opciones de la orden change:

| Opciones                    | Descripción                                                  |
| --------------------------- | ------------------------------------------------------------ |
| change -d ult_dia usuario   | Fcha del último cambio de password                           |
| change -m min_dias usuario  | Nº días que han de pasar para cambiar la contraseña          |
| change -M max_dias usuario  | Nº días máximo que puede estar la misma contraseña sin cambiarla |
| change -W warn_dias usuario | Nº días antes de que la contraseña expire                    |
| change -I inac_dias usuario | Nº de días después de que la contraseña expire               |
| change -E exp_dias usuario  | Fecha  en la cuenta expira y se deshabilita automáticamente  |



### 4.3 Gestión de grupos

Un grupo es un conjunto de usuarios que comparten recursos o archivos del sistema. Un grupo se caracteriza por:

- Nombre del grupo, o **groupname**
- Identificador del grupo (**GID**), que es un número que permite al sistema identificar al grupo
- Archivo de configuración **/etc/group**, que tiene el formato **nombre: x: gid:lista de usuarios**

Algunas ódenes relacionadas con la gestión de grupos es:

| Comandos              | Descripción                                                  |
| --------------------- | ------------------------------------------------------------ |
| groupadd grupo        | Crea un nuevo grupo                                          |
| groupmod grupo        | Modifica el grupo existente                                  |
| groupdel grupo        | Elimina un grupo                                             |
| newgrp grupo          | Cambia el grupo activo                                       |
| gpasswd grupo         | Asigna una contraseña a un grupo                             |
| gpasswd -a user grupo | Añade usuario a un grupo                                     |
| groups [usuario]      | Informa de los grupos a los que pertenece un usuario         |
| id [usuario]          | Lista el identificador del usuario y los grupos a los que pertenece |
| grpck                 | Comprueba la consistencia del archivo de grupos              |



```bash
$ groupadd Grupo1 
$ usermod -g Grupo1 Pablo
$ su Pablo
$ id
uid=500(Pablo) gid=503(Grupo1)
```



### 4.4 Usuarios y grupos especiales

Los usuarios especiales son aquellos que no estan asociados a personas fíicas.

| Usuarios                            | Descripción                               |
| ----------------------------------- | ----------------------------------------- |
| root                                | Usuario administrador                     |
| bin, daemon, lp, sync, shutdown,... | Para poseer archivos y ejecutar servicios |
| mail, news, ftp, ...                | Asociados a herramientas                  |
| postgres, mysql, xfs, ...           | Para administrar y ejecutar servicios     |
| nobody ó nfsnobody                  | Usado por NFS                             |



### 5. Organización del sistema de archivos y gestión básica de archivos

(La primera parte es repaso de FS, por lo cual prescindiré de resumirla. Podeis encontrar los apuntes en la parte dedicada a primero dentro de este mismo git. Es interesante mirar los apuntes del profesor, ya que prescindo también de la parte puramente teórica, donde habla del  FHS o Filesystem Hierarchy Standard, la cual sirve para ponernos en contexto sobre lo que vamos a trabajar a continuación)

##### 5.2.1 Acceso a información del SO relativa al sistema de archivos

Para obtener información de los sistemas de archivos debemos acceder a ***/etc/fstab*** y ***/etc/mtab***.

La información que se muestra en ***/etc/fstab*** es muy útil para comprender las opciones de montaje que se han realizado para cada uno de los sistemas de archivos que tenemos accesibles en nuestro sistema. Algunas de las opciones que refleja son:

- Modo de acceso a los archivos: **{rw|ro}** (lectura/escritura o solo lectura)
- Modo de acceso SUID: **{suid|nosuid}**
- Montaje automático: **{auto|noauto}**
- Ejecución de archivos: **{exec|noexec}**
- Cuotas de usuario y de grupo: **usrquota, grpquota**
- Valores por defecto de montaje **(defaults):  rw, suid, dev, exec, auto, nouser,async**
- Permitir a los usuarios montar un sistema de ficheros : **user, users, owner.*
- Propietario y grupo propietario de los ficheros del SA : **uid=500, gid=100**



Otro directorio muy útil para obtener información es el **/proc**, el cual soporta el sistemas de archivos virtual **proc**. Este directorio contiene archivos de texto que permiten acceder a la información de estado del sistema. Los archivos mas interesantes que podemos encontrar son:

- **/proc/filesystems**: Enumera todo los tipos de sistemas de archivos disponibles
- **/proc/mounts**: Muestra los sistemas de archivos mostrados actualmente



