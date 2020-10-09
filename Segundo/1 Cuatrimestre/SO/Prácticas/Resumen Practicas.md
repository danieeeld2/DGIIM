# PRÁCTICA SISTEMAS OPERATIVOS

###### DANIEL ALCONCHEL VÁZQUEZ

------

## <u>Sesión 1</u>

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



## <u>Sesión 2</u>

Comencemos recordando algunos de los tipos  de archivos que encontramos en el SO:

- **Archivos regulares**: Archivos de programas y datos.
- **Directorios**: Archivos diseñados para soportar la estructura jerárquica.
- **Enlances simbólicos**: Permite referenciar a otros archivos desde distintas ubicaciones.
- **Archivos especiales de dispositivos**: Estos archivos representan dispositivos y permitenal usuario del lenguaje de órdenes del shell y a los programadores de aplicacionestrabajar sobre los dispositivos como si se tratase de un archivo normal. 
- Archivos para comunicaciones **FIFO **.
- Archivos para comunicaciones **Socket**.

### 

### 3. Partición de dispositivos de almacenamiento secundario

Para poder utilizar un dispositivo de almacenamiento secundario (drive), como puede ser un disco duro o una memoria flash, en un SO es necesario, en primer lugar, establecer secciones (**particiones**) dentro del dispositivo físico, que sean identificables, y que permitan alojar un SA concreto. Al proceso de establecer e identificar estas particiones en el dispositivo se le denomina comúnmente  **partición de disco**.

Una partición está constituida por un conjunto de sectores que van a formar lo que podemos denominar un *disco lógico*. Es necesario asociarle una etiqueta que indica el tipo de SA que va a alojar cuando posteriormente se formatee.

El número de particiones que podemos establecer en un dispositivo bajo una arquitectura Intel está limitado debido a la *“compatibilidad hacia atrás”*. La primera ***tabla de particiones*** se almacenaba como parte del ***sector de arranque maestro (master boot record, MBR)*** y solamente tenía espacio para almacenar cuatro entradas, conocidas como **particiones primarias**.

#### 3.1 ¿Cuántas particiones hago en mi dispositivo?

Dependiendo si el dispositivo actua como ***dispositivo de arranque (Boot drive)*** o no, será necesario establecer una distribución de particiones u otra. Un dispositivo de arraque va a ser el dispositivo que utilice en primer lugar la BIOS de nuestra arquitectura para cargar en memoria el programa SO.

Si queremos que nuestro SO arranque desde el dispositivo donde vamos a realizar las particiones necesitamos establecer la siguiente configuración:

- Partición primaria
- Una o más particiones **swap**
- Tantas particiones primarias o lógicas como uno desee

En caso de que no actue como dispositivo de arranque, se usará la siguiente configuración:

- Una o más particiones primarias o lógicas
- Ninguna o las que quieras particiones swap.

#### 3.2 ¿Qué directorios de primer nivel del estándar FHS deberían estar soportados por una partición independiente?

Toda la estructura del FHS puede estar soportada por una única partición, pero es conveniente establecer particiones independientes, que soporten la información que se almacena en determinados directorios de la estructura.

| Directorio | Descripción                                                  |
| ---------- | ------------------------------------------------------------ |
| **/home**  | Almacena los directorios de inicio de los usuarios. Podemos establecer una partición independiente y, de esta forma, limitar de esta forma el espacio de almacenamiento permitido para los mismos. Además, de cara a instalar nuevas versiones, si el **/home** está soportado en una partición independiente no tendremos probleas con nuestra partición raiz y podremos formatearla y en ella instalar la nueva versión del SO |
| **/usr**   | Almmacena la mayoría de los ejecutables binarios del sistema |
| **/var**   | Contiene los directorios de SPOOL                            |



#### Actividad: Partición de un dispositivo

Para esta actividad vamos a usar un dispositivo simulado mediante un archivo **/dev/loop?**, que permite crear un dispositivo de almacenamiento virtual, cuyo espacio de almacenamiento viene soportado por un archivo asociado. Para crearlos:

```bash
#Creamos dos /dev/loop

$ mknod /dev/loop0 b 7 0
$ mknod /dev/loop1 b 7 1

#Creamos un archivo de 20 MB y otro de 30 MB:

$ dd if=/dev/zero of=/root/archivo_SA20 bs=2k count=10000
$ dd if=/dev/zero of=/root/archivo_SA30 bs=3k count=10000

# Asociamos los archivos de dispositivo loop a los archivos que acabamos de crear

$ losetup /dev/loop0 /root/archivo_SA20
$ losetup /dev/loop1 /root/archivo_SA30

# Comprobamos la configuración 

$ fdisk -l /dev/loop0 /dev/loop1

Disk /dev/loop0: 20 MB, 20480000 bytes
255 heads, 63 sectors/track, 2 cylinders, total 40000 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

Disk /dev/loop0 doesn't contain a valid partition table

Disk /dev/loop1: 30 MB, 30720000 bytes
255 heads, 63 sectors/track, 3 cylinders, total 60000 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

Disk /dev/loop1 doesn't contain a valid partition table

```

Si vas a usar un dispositivo físico, como un pen drive, conectalo al puerto correspondiente y desmonta el dispositivo.

A continuación, procedemos a crear la tabla de particiones mediante **fdisk**. Una vez acabado, vemos si las particiones son correctas:

```bash
$ fdisk /dev/loop0
Command (m for help): m
	a   toggle a bootable flag
   	b   edit bsd disklabel
    c   toggle the dos compatibility flag
    d   delete a partition
    l   list known partition types
    m   print this menu
    n   add a new partition
    o   create a new empty DOS partition table
    p   print the partition table
    q   quit without saving changes
    s   create a new empty Sun disklabel
    t   change a partition's system id
    u   change display/entry units
    v   verify the partition table
    w   write table to disk and exit
    x   extra functionality (experts only)

Command: n
Command action
   e   extended
   p   primary partition (1-4)
p
# Le damos a Enter para que se haga automático
Partition number (1-4, default 1): 
Using default value 1
First sector (2048-39999, default 2048): 
Using default value 2048
Last sector, +sectors or +size{K,M,G} (2048-39999, default 39999): 
Using default value 39999
Command: w

$ fdisk -l /dev/loop0
Disk /dev/loop0: 20 MB, 20480000 bytes
125 heads, 58 sectors/track, 5 cylinders, total 40000 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0xd5a06c53

      Device Boot      Start         End      Blocks   Id  System
/dev/loop0p1            2048       39999       18976   83  Linux

# Análogo para el segundo
```



### 4. Asignación de un Sistema de Archivos a una partición (formateo lógico)

Una vez que disponemos de las particiones en nuestro dispositivo de almacenamiento secundario, debemos proceder a asignar el sistema de archivos adecuado a cada una de las particiones. En Linux, a parte del SA específico para las particiones especialmente dedicadas a intercambio (**swap**), se utilizan, normalmente, tres sistemas de archivos: **ext2, ext3 y ext4**.

- **ext2**: Sistema de archivos de disco de alto rendimiento usado para discos duros, memorias flash y medios extraibles, ofreciendo el mejor rendimiento en velocidad de transferencia de E/S y uso de CPU.
- **ext3**: Versión del *ext2* que incluye ***journaling***, mecanismo por el cual un sistema informático puede implementar *transacciones*. Se basa en llevar un regisro diario en el que se almacena la información necesaria para restablecer datos afectados por la transacción, en caso de que esta falle.
- **ext4**: El estándar actual. Es similar al *ext3*, pero presenta las siguientes mejoras:
  - **Extensiones**: Permiten describir un conjunto de bloques de disco contiguos, mejorando de esta forma el rendimieno E/S al trabajar con archivos de gran tamaño y reduciendo la fragmentación de disco.
  - **Asignación retardada de espacio en disco**: Permite postergar en el tiempo la asignación de bloques de disco hasta el momento real en el que va a realizar la escritura.



#### Actividad: Creación de sistemas de archivos

Volviendo a la actividad anterior, el objetivo de esta actividad es formatear las particiones creadas con anterioridad de forma consistente con el tipo SA que vayamos a alojar.

La orden que nos permite hacer dicha acción es **mke2fs**.

```bash
$ mke2fs -t ext? /dev/loop? #Build a fylesystem on a specific device
$ mke2fs -L LABEL_ext? /dev/loop? # Set a Volume Label for Partition
```



```bash
$ mke2fs -t ext3 /dev/loop0
mke2fs 1.41.12 (17-May-2010)
Filesystem label=
OS type: Linux
Block size=1024 (log=0)
Fragment size=1024 (log=0)
Stride=0 blocks, Stripe width=0 blocks
5016 inodes, 20000 blocks
1000 blocks (5.00%) reserved for the super user
First data block=1
Maximum filesystem blocks=20709376
3 block groups
8192 blocks per group, 8192 fragments per group
1672 inodes per group
Superblock backups stored on blocks: 
	8193

Writing inode tables: done                            
Creating journal (1024 blocks): done
Writing superblocks and filesystem accounting information: done

$ mke2fs -L LABEL_ext3 /dev/loop0
mke2fs 1.41.12 (17-May-2010)
Filesystem label=LABEL_ext3
OS type: Linux
Block size=1024 (log=0)
Fragment size=1024 (log=0)
Stride=0 blocks, Stripe width=0 blocks
5016 inodes, 20000 blocks
1000 blocks (5.00%) reserved for the super user
First data block=1
Maximum filesystem blocks=20709376
3 block groups
8192 blocks per group, 8192 fragments per group
1672 inodes per group
Superblock backups stored on blocks: 
	8193

Writing inode tables: done                            
Writing superblocks and filesystem accounting information: done

This filesystem will be automatically checked every 23 mounts or
180 days, whichever comes first.  Use tune2fs -c or -i to override.

$ fdisk -l /dev/loop0
Disk /dev/loop0: 20 MB, 20480000 bytes
255 heads, 63 sectors/track, 2 cylinders, total 40000 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000
```



### 5. Ajustes de parámetros configurables de un SA y comprobación de errores

Una vez listo los sistemas de archivos, podemos usar la orden **tune2fs**, que nos permite ajustar determinados parámetros de los mismos. Algunas funciones son:

| Etiqueta                          | Descripción                                                  |
| --------------------------------- | ------------------------------------------------------------ |
| -l  *dispositivo*                 | Muestra por pantalla el contenido del superbloque del SA     |
| -c max-mount-counts *dispositivo* | Establece el número máximo de montajes que se puede llegar a realizar sin que se realice una comprobación de la consistencia del SA |
| -L label *dispositivo*            | Poner una etiqueta al SA                                     |



Con el tiempo, las estructuras del SA pueden llegar a corromperse. Esta situación podría provocar la  degradación en el rendimiento del sistema e incluso situaciones de pérdida de información. Para solucionarlo, Linux automatiza el proceso de comprobación, pero pueden ocurrir situaciones en las que sea necesario que el administrador ejecute manualmente las comprobaciones. Para ello se usa la herramienta **fsck**.



#### Actividad: Personalización de los metadatos del SA

Consultando el manual en línea para la orden **tune2fs** responde a las siguientes preguntas:

a) ¿Cómo podrías conseguir que en el siguiente arranque del sistema se ejecutara automáticamente **e2fsck** sin que se haya alcanzado el máximo número de montajes?

```bash
#Pendiente
```

b) ¿Cómo podrías conseguir reservar para uso exclusivo de un usuario username un número de bloques del sistema de archivos?

```bash
#Pendiente
```



### 6. Montaje y desmontaje del Sistema de Archivos

Una vez que disponemos de nuestros sistemas de archivos, ya solo queda ponerlos a disposición del usuario, haciendo que puedan ser accesibles dentro de la jerarquía de directorios. Para ello utilizaremos la orden **mount** (Para desmontarlo se utiliza **umount**).

Hablamos *de montaje de un sistema de archivos*, en el sentido de añadir una nueva rama al espacio de nombres. Para montar un sistea de archivos es necesario solamente indicar en qué directorio se montará.



Como vimos anteriormente, el archivo **/etc/fstab** es el archivo de configuración que contiene la información sobre todos los sistemas de archivos que se pueden montar y de las zonas de intercambio a activar. Utiliza el siguiente formato:

​					**< file system > < mount point > < type > < options > < dump > < pass >**

- **< file system > **, es el número que identifica el archivo especial de lo bloques
- **< mount point >** , esel directorio que actua como punto de montaje.
- **< type >**, tipo de sistema de archivos.
- **< options >**, son las opciones que se utilizarán en el proceso de ensamblado.
  - **rw**: Lectura y escritura.
  - **ro**: Sólo lectura.
  - **suid/nosuid**: Permitido el acceso en modo SUID o no permitido.
  - **auto/noauto**: Montar automáticamente o no montar automáticamente.
  - **exec/noexec**: Permitir la ejecución de ficheros o no.
  - **usrquota, grpquota**: Cuotas de usuario y de grupo.
  - **defaults = rw, suid, dev, exec, auto, nouser, async**
  - **user, users, owner**. Permitir a los usuarios montar un sistema de archivos.
  - **uid=500, gid=100**: Propietario y grupo propietario de los archivos del SA.
  - **umask**: Máscara para aplicar los permisos a los archivos.
- **< dump >**, frecuencia con la que se realiza una copia de seguridad.
- **< pass >**, durante el arranque del sistema, especifica el orden en el que fsck realizará las comprobaciones sobre los SAs.



#### Actividad: Montaje de sistemas  de archivos

Utiliza el manual para descubrir la forma de montar nuestros SAs de manera que cumpla:

1) El SA etiquetado como LABEL_ext3 debe estar montado en el directorio /mnt/SA_ext3 y en modo de solo lectura.

```bash
$ vi /etc/fstab

#Añadimos la siguiente línea
LABEL=LABEL_ext3        /mnt    ext3    ro      0       0

$ mount -L LABEL_ext3
/dev/loop0             19M  170K   18M   1% /mnt
```

2)  El SA etiquetado como LABEL_ext4 debe estar montado en el directorio /mnt/LABEL_ext4 y debe tener sincronizadas sus operaciones de E/S de modificación de directorios.

```bash
$ vi /etc/fstab

#Añadimos la siguiente línea
LABEL=LABEL_ext4        /mnt    ext4    defaults      0       0

$ mount -L LABEL_ext4

$ df -h | grep /dev/loop1
/dev/loop1             29M  365K   27M   2% /mnt
```



### 7. Administración de software

El software a instalar en sistemas Linux se estructura en paquetes. Un **paquete de software** es un archivo que contiene un conjunto de programas complementarios, y, en la mayoría de los casos, tienen dependencia con otros paquetes. Los paquetes pueden incluir archivos con programas en código binario, o bien en formato de código fuente junto con las instrucciones para generar el código binario,

Las herrmientas para la gestión de estos paquetes se conocen como **gestores de paquetes**. 

La forma más simplede instalar y actualizar software en un sistema es mediante el uso de los gestores que proporciona el propio SO. Por ejemplo, los Linux basados en Debian se identifican por tener la extensión **".deb"** en el nombre del archivo del paquete. Otros, como los basados en Red Hat, usan **".rpm"**. Estos son los dos con los que trabajaremos en esta asignatura, ya que el primero corresponde al que usamos en Ubuntu y el segundo a Fedora.



|                   | Formato .deb            | Formato .rpm                 |
| ----------------- | ----------------------- | ---------------------------- |
| **Modo Terminal** | dpkg, apt-get, aptitude | rpm, YUM, apt-get            |
| **Modo Gráfico**  | Synaptic, Adept...      | Synaptic, yumex, Kpackage... |



Dentro de los gestores de paquetes de línea están:

- Los de alto nivel, como apt-get o YUM.  Permiten realizar atualizaciones automáticas, incluyen análisis de dependencias, procesamiento de paquetes obsoletos...
- Los de bajo nivel como dpkg y rpm. Suelen ser más precisos y potentes



#### 7.2.1 APT y YUM

Algunas órdenes útiles de YUM son:

| Órdenes de YUM      | Descripción                                                  |
| ------------------- | ------------------------------------------------------------ |
| yum list            | Lista de paquetes disponibles en los repositorios para instalar |
| yum list installed  | Lista de paquetes instalados                                 |
| yum list updates    | Lista de paquetes con actualizaciones disponibles en los repositorios |
| yum install paquete | Instala el paquete especificado                              |
| yum update          | Actualiza los paquetes instalados                            |
| yum remove paquete  | Elimina el paquete especificado                              |



#### Actividad: Trabajo con el gestor de paquetes YUM

Encuentra los archivos de configuración de YUM y explora las distintas órdenes disponibles en YUM ejecutándose. En concreto, lista todos los paquetes instalados y disponibles, elimina alguno de los paquetes instalado haciendo uso de los paquetes que se encuentran disponibles en **/fenix/depar/lsi/so/paquetes**. 

```bash
$ mount none /mnt/ -t hostfs -o /tmp/paquetes #Para montar los paquetes
#rpm -i para ir instalando los paquetes

$ yum list installed
python-iniparse.noarch      0.4-2.fc14                  @febootstrap/$releasever
$yum remove yum.noarch
$yum install yum.noarch
```



#### 7.2.2 RPM

RPM comprueba dependencias eincluye opciones como la verificación de la revisión y las firmas de seguridad de privacidad de GNU que permite que los paquetes se distribuyan con seguridad.

La bases de datos en nuestra computadora registran las versiones de los paquetes Linux, véase directorio /var/lib/rpm que es el que utiliza RPM.

```bash
$ rpm <opciones><nombres-paquetes>
```

- **rpm -i < nombre-archivo-paquete >**: Instala paquetes. Si la operación tiene éxito no se mostrará ningún mensaje
- **rpm -e < nombre-paquete >**: Elimina paquetes. Si la operación tiene éxito no se mostrará ningún mensaje
- **rmp -U < nombre-archivo-paquete >**: Actualización de descargas de paquetes. Con la opción -U incluye la eliminación automática de la versión de paquete previamente instalada
- **rpm -F < nombre-servidor-HTTP/FTP >**: Se busca el paquete en el servidor designado en Internet y se preparará la correspondiente actualización
- **rpm -qa | grep < parte-nombre-paquete-buscado > | sort**: Esta línea de órdenes puede utilizarse para buscar paquetes instalados por su nombre
- **rpm -qi < nombre-paquete >**: Muestra información precisa del paquete instalado
- **rpm -V < nombre-paquete >**: Consulta en la base de datos paraverificar la instalación de unpaquete recientemente instalado.



#### Actividad: Trabajo con el gestor de paquetes rpm

```bash
#Mostrar información general de un paquete ya instalado
$ rpm -qi libselinux-utils-2.0.96-6.fc14.1.i686 

#Mostrar solo los archivos de configuración
$rpm -qc libselinux-utils-2.0.96-6.fc14.1.i686 
/etc/ssh/moduli

#Mostrar paquetes requeridos por un paquete determinado del sistema
$rpm -q libselinux-utils-2.0.96-6.fc14.1.i686 --whatrequires
no package requires libselinux-utils-2.0.96-6.fc14.1.i686

#Instalar paquete quota
$rpm -q quota-3.17-13.fc14.i686.rpm --whatrequires
no package requires quota-3.17-13.fc14.i686.rpm
$rpm -i quota-3.17-13.fc14.i686.rpm

#Instalar y desinstalar el paquete sysstat
$rpm -q sysstat-9.0.6-3.fc13.i686.rpm  --whatrequires
no package requires sysstat-9.0.6-3.fc13.i686.rpm
$rpm -i sysstat-9.0.6-3.fc13.i686.rpm 
warning: sysstat-9.0.6-3.fc13.i686.rpm: Header V3 RSA/SHA256 Signature, key ID e8e40fde: NOKEY
	package sysstat-9.0.6-3.fc13.i686 is already installed
$ rpm -e sysstat-9.0.6-3.fc13.i686.rpm


```



### 8. Administración de quotas

Existe una forma flexible de limitar el uso de disco por parte de los usuarios del sistema. Este control se lleva a cabo mediante un sistema de **cuotas**. Las cuotas de disco permien limitar el número de recursos de un SA que va a poder utilizar el usuario. Estos recursos son los bloques de disco y los i-nodos.

Para poder trabajar con el sistema de cuotas en Linux es necesario tener instalado el paquete **quota**.

El sistema de cuotas permite establecer límites para usuarios y/o grupos o para bloques y/o i-nodos:

- **Límite hard**: El usuario no puede sobrepasarlo. Si llegara a sobrepasarlo, el sistema no le permitirá usar más bloques, por lo que no pordrá ampliar el tamaño de sus archivos ya creados, ni tampoco i-nodos, por lo que no podrá crear nuevos archivos.
- **Límite soft**: Debe configurarse como un número de recursos inferior al límite hard y se puede sobrepasar durante cierto tiempo, pero sin llegar a superar el límite hard. Una vez pasado el tiempo se comporta como si hubiera superado el límite hard.



#### Actividad: Sistema de cuotas para el sistema de archivos tipo ext4

```bash
# Editar /etc/fstab y activarel sistema de cuotas para el usuario ext4 (usrquota)

# Volver a montar el dispositivo
$ mount -o remount /mnt/

# Crear el archivo que permite llevar el control de cuotas de usuario para el SA. El nombre de este archivo es aquota.user
$ quotacheck -nm /mnt/
$ ls /mnt/
aquota.user    

# Procedemos a activar el sistema de control de cuotas de usuario
$ quotaon -a

# Ahora solo falta editar la cuota para cada usuario del sistema mediante la siguiente orden. Puede ser buena idea inspeccionar /etc/passwd para localizar los nombres:
$ edquota username # Por ejemplo smmsp
$ edquota smmsp
Disk quotas for user smmsp (uid 51):
  Filesystem                   blocks       soft       hard     inodes     soft
   hard
  /dev/loop1                       56          0          0         14        0 
      0


# Para finalizar el periodo de gracia para el límite soft
$ edquota -t
  Filesystem             Block grace period     Inode grace period
  /dev/loop1                    7days                  7days

```



Algunas órdenes útiles para trabajar con cuotas son:

- **quota username**: Asigna las cuotas para un usuario
- **repquota < SA >**: Estadística de las cuotas para todos los usuarios.