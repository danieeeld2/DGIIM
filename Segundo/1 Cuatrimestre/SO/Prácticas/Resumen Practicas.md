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

![](/home/daniel/Git/DGIIM/Segundo/1 Cuatrimestre/SO/Prácticas/Imagenes/1.png)

![](/home/daniel/Git/DGIIM/Segundo/1 Cuatrimestre/SO/Prácticas/Imagenes/2.png)



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



## <u>Sesión 3</u>

### 3. Control y gestión de CPU

En este punto veremos algunas órdenes para comprobar el estado del siste,a y su rendimiento



#### 3.1. Orden *uptime*

Muestra en una línea la siguiente información:

**< hora actual >< tiempo que lleva el sistema en marcha >< nº usuarios conectados >< carga media del sistema en los últimos 1, 5, 15 minutos >**

La órden **w** muestra la misma información y, además, lo que está haciendo cada usuario conectado.

```bash
$ uptime
 14:10:13 up 8 min,  1 user,  load average: 0.00, 0.00, 0.00
$ w
 14:10:27 up 8 min,  1 user,  load average: 0.00, 0.00, 0.00
USER     TTY      FROM              LOGIN@   IDLE   JCPU   PCPU WHAT
root     tty0     -                14:01    0.00s  0.00s  0.00s w
```



#### Actividad: Consulta de estadísticas del sistema

Responde a las siguientes cuestiones y especifica, para cada una, la opción que has utilizado:

a) ¿Cuánto tiempo lleva en marcha el sistema?

```bash
# Usamos uptime y nos fijamos en la información de después del up
$ uptime
 14:10:13 up 8 min,  1 user,  load average: 0.00, 0.00, 0.00 # up 8 min
```

b) ¿Cuántos usuarios hay trabajando?

```bash
# Usamos uptime y nos fijamos en el número que acompaña a la palabra user
$ uptime
 14:10:13 up 8 min,  1 user,  load average: 0.00, 0.00, 0.00 # 1 user
```

c) ¿Cuál es la carga media del sistema en los últimos 15 minutos?

```bash
# Usamos uptime y nos fijamos en el último número
$ uptime
 14:10:13 up 8 min,  1 user,  load average: 0.00, 0.00, 0.00 # 0.00
```



#### 3.2. Orden *time*

Mide el tiempo de ejecución de un programa y muestra un resumen del uso de los recursos del sistema. Muestra el tiempo en el siguiente formato:

​		**< tiempo real > < tiempo en modo usuario > < tiempo en modo supervisor (sys) >**

Para calcular el tiempo de espera de un proceso: **T.espera = real - user - sys**

```bash
$ time ps
  PID TTY          TIME CMD
 1180 tty0     00:00:00 bash
 1210 tty0     00:00:00 ps

real	0m0.058s
user	0m0.000s
sys	0m0.000s
```



#### 3.3. Órdenes *nice* y  *renice*

Linux realiza una planificación por prioridades. Por defecto, un proceso hereda la prioridad de un proceso padre.

- **nice**: Permite establecer un valor de prioridad a un proceso, distinto del que traía por defecto. El rango de valores que permite establecer es [-20,19].

  Asignar un valor negativo aumenta la posibilidad de ejecución de un proceso y solo lo puede hacer **root**. Los usuarios sin privilegios de administración solo pueden usar valores positivos.

  ```bash
  $ nice -5 konqueror # Aumenta en 5 el valor de prioridad de la ejecución dekonqueror
  $nice −−10 konqueror # Decrementa en 10 el valor de prioridad (sólo usuario root)
  ```

- **renice**: Permite alterar la prioridad de uno o más procesos de ejecución

  ```bash
  $ renice 14 890 # Aumenta en 14 la prioridad del proceso 890
  ```



#### Actividad: Prioridad de los procesos

a) Crear una script que realice un ciclo de un número variable de iteraciones en el que se hagan dos cosas: una operación aritmética y el incremento de una variable. Cuando terminen las iteraciones escribirá un mensaje en pantalla  indicando el valor actual de la variable.

```bash
$ touch prueba_procesos
$ vi prueba_procesos

#!/bin/bash

i=0;
for (( ; i < $1 ; i++ )); do
        i=$(( $i + 1 ));
        x=$(( $i + 10 ));
done;

echo $i;

$ chmod +x prueba_procesos
$ ./prueba procesos 10
10
```

b) Ejecuta el guión anterior varias veces en background y comprueba su prioridad inicial. Cambia la prioridad de dos de ellos, a uno lo aumentas y a otro se la disminuyes, ¿cómo se comporta el sistema para estos procesos?

```bash
$ nice --adjustment=3 ./prueba_procesos 100001 &
$ nice --adjustment=-3 ./prueba_procesos 100002 &
100002
100001

# Ejecuta antes el de prioridad negativa (probabilidad más favorable de que se ejecute)
```

c) Obtén los tiempos de finalización de cada uno de los guiones del apartado anterior

```bash
$ time nice --adjustment=3 ./prueba_procesos 100001
$ time nice --adjustment=-3 ./prueba_procesos 100002
10001
real	0m0.214s
user	0m0.200s
sys	0m0.050s

10002
real	0m0.187s
user	0m0.180s
sys	0m0.000s

```



#### 3.4. Orden *pstree*

Permite visualizar un árbol de procesos de ejecución. Algunas opciones que trae son:

| Opciones | Descripción                                                  |
| -------- | ------------------------------------------------------------ |
| **-a**   | Muestra argumentos de la línea de ódenes                     |
| **-A**   | Usa caracteres ASCII para dibujar el árbol                   |
| **-G**   | Uso de caracteres de VT100                                   |
| **-h**   | Resalta el proceso actual y sus antepasados                  |
| **-H**   | Igual que el anterior, pero para el proceso que se especifique |
| **-l**   | Usa formato largo                                            |
| **-n**   | Ordena los procesos por el PID  de su antecesor              |
| **-p**   | Desactiva el mostrar los PID entre paréntesis después del nombre de cada proceso |
| **-u**   | Si el uid de un proceso es diferente del de su padre, el nuevo uid se pone entre paréntesis |
| **-V**   | Información sobre la versión                                 |
| **-Z**   | Muestra el contexto de seguridad de cada proceso             |

```bash
$ pstree
init-+-auditd---{auditd}
     |-crond
     |-login---bash---pstree
     |-rsyslogd---2*[{rsyslogd}]
     |-sendmail
     `-sshd
```

#### 

#### 3.5. Orden *ps*

Esta orden se implementa usando el psudo-sistema de archivos **/proc**. Muestra la siguiente información de los procesos en ejecución:

- **USER**: Usuario que lanzó el programa
- **PID**: Identificador de un proceso
- **PPID**: Identificador del proceso padre
- **%CPU**: Porcentaje entre el tiempo usado realmente y el que lleva en ejecución
- **%MEM**: Fraxción de memoria consumida
- **VSZ**: Tamaño virtual del proceso en KB
- **RSS**: Memoria real usado en KB
- **TTY**: Terminal asociada al proceso
- **STAT**: Estado del proceso, que puede ser:
  - **R**: En ejecución o listo
  - **S**: Durmiendo
  - **T**: Parado
  - **Z**: Proceso Zombie
  - **D**: Durmiendo ininterrumplibemente
  - **N**: Prioridad baja (>0)
  - **<**: Prioridad alta (<0)
  - **s**: Lider de sesión
  - **l**: Tiene multi-thread
  - **+**: Proceso foreground
  - **L**: Páginas bloqueadas en memoria

Esta órden se suele ejecutar con la opción **-ef**, donde la *e* significa procesos que están en el sistema y *f* para que muestre la información completa. Sin argumentos muestra los procesos lanzados por el usuario que ejecuta esta orden.



#### Actividad: Jerarquía e información de procesos

a) La orden **pstree** muestra el árbol de procesos que hay en ejecución. Comprueba que la jerarquía mostrada es correcta mediante la orden **ps**.

```bash
$ pstree
init-+-auditd---{auditd}
     |-crond
     |-login---bash---pstree
     |-rsyslogd---2*[{rsyslogd}]
     |-sendmail
     `-sshd
$ ps
  PID TTY          TIME CMD
 1180 tty0     00:00:00 bash
 1201 tty0     00:00:00 ps
 
 # Es correcta
```

b) Ejecuta la orden **ps** con la opción **-A**, ¿ qué significa que un proceso tenga un carácter **"?"** en la comuna etiquetada como **TTY**?

```bash
$ ps -A
  PID TTY          TIME CMD
    1 ?        00:00:00 init
    2 ?        00:00:00 kthreadd
    3 ?        00:00:00 ksoftirqd/0
    4 ?        00:00:00 kworker/0:0
    5 ?        00:00:00 kworker/u:0
    6 ?        00:00:00 rcu_kthread
    7 ?        00:00:00 watchdog/0
    8 ?        00:00:00 cpuset
    9 ?        00:00:00 khelper
   10 ?        00:00:00 kworker/u:1
  115 ?        00:00:00 sync_supers
  117 ?        00:00:00 bdi-default
  118 ?        00:00:00 kblockd
  134 ?        00:00:00 rpciod

# Significa unkonw value, es decir, no hay una terminal asociada al proceso
```



#### 3.6. Orden *top*

Esta orden proporciona una visión continuada de la actividad de un rpoceso en tiempo real, muestra lastareas que más uso hacen de la CPU. Las 5 primeras líneas muestran información general del sistema:

- Estadística de la orden **uptime** 
- Estadísticas sobre los procesos del sistema (número de procesos, procesos enejecución, durmiendo, parados o zombies)
- Estado actual de la CPU  (porcentaje en uso por usuarios, por el sistema, porprocesos con valor nice positivo, por procesos esperando E/S, CPU desocupada,tratando interrupciones hardware o software, en espera involuntaria porvirtualización)
- Memoria (memoria total disponible, usada, libre, cantidad usada en buffers y enmemoria caché de página)
- Espacio del swap (swap total disponible, usada y libre)

Los datos de la parte de abajo son parecidos a **ps**, excepto SHR, que muestra la cantidad de memoria compartida.

Esta orden permite, también, realizar una serie de acciones sobre los rpocesos de forma interactiva:

- **r**: Cambiar prioridad de un proceso
- **k**: Matar o enviar una señal
- **N**: Ordenarlos por PID
- **P**: Ordenarlos por CPU
- **n**: Cambiar el número de procesos que se muestran
- **q**: Para salir

```bash
$ top
11:49:35 up 37 min,  1 user,  load average: 0.00, 0.00, 0.00
Tasks:  36 total,   1 running,  35 sleeping,   0 stopped,   0 zombie
Cpu(s):  0.0%us,  0.0%sy,  0.0%ni,100.0%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
Mem:   1019252k total,    38416k used,   980836k free,     3468k buffers
Swap:        0k total,        0k used,        0k free,    17516k cached

  PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND            
    1 root      20   0  2884 1316 1152 S  0.0  0.1   0:00.02 init               
    2 root      20   0     0    0    0 S  0.0  0.0   0:00.00 kthreadd           
    3 root      20   0     0    0    0 S  0.0  0.0   0:00.63 ksoftirqd/0        
    4 root      20   0     0    0    0 S  0.0  0.0   0:00.00 kworker/0:0        
    5 root      20   0     0    0    0 S  0.0  0.0   0:00.00 kworker
```



#### 3.7. Orden *mpstat*

Muestra estadísticas del procesador del sistema junto con la media gloal de todos los datos mostrados. La información de lacabezera hace referencia a:

- **CPU**: Número del procesador
- **%user**: Porcentaje de uso de la CPU con tareas a nivel de usuario
- **%nice:** Porcentaje de uso de la CPU con tareas a nivel de usuario con prioridad “nice” (>0)
- **%sys:** Porcentaje de uso de la CPU para tareas del sistema (no incluye el tratamiento de interrupciones) 
- **%iowait:** Porcentaje de tiempo que la CPU estaba “desocupada” mientras que el sistematenía pendientes peticiones de E/S
- **%irq:** Porcentaje de tiempo que la CPU gasta con interrupciones hardware
- **%soft:** Porcentaje de tiempo que la CPU gasta con interrupciones software (la mayoríason llamadas al sistema)
- **%idle:** Porcentaje de tiempo que la CPU estaba “desocupada” y el sistema no tienepeticiones de disco pendientes
- **intr/s:** Número de interrupciones por segundo recibidas por el procesador

La sistaxis de la orden es **mpstat [intervalo] [número] **, donde el intervalo es cada cuántos segundos debe mostrar datos y cuántos muestra

```bash
$ mpstat 
Linux 3.0.4 (localhost) 	10/10/20 	_i686_	(1 CPU)

12:00:19     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest   %idle
12:00:19     all    0.02    0.00    0.00    0.10    0.00    0.00    0.00    0.00   99.88

```



#### Actividad: Estadística de recursos del sistema

Responde a las siguientes cuestiones y especifíca,para cada una, la orden que has utilizado:

a) ¿Qué porcentaje de tiempo de CPU se ha usado para atender a las interrupciones de hardware?

b) ¿Y en iterrupciones de software?

c) ¿Cuánto espacio de swap está libre y cuánto está ocupado?

```bash
# Para las tres usamos la orden top y nos fijamos en la línea correspondiente
$ top
Tasks:  38 total,   1 running,  37 sleeping,   0 stopped,   0 zombie
Cpu(s):  0.0%us,  0.0%sy,  0.0%ni,100.0%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
Mem:   1019252k total,    74592k used,   944660k free,     4904k buffers
Swap:        0k total,        0k used,        0k free,    50692k cached
```



### 4. Control y gestión de memoria

#### 4.1. Orden *free*

Si queremos centrar la monitorización únicamente en el uso de memoria podemos usar esta orden, la cual, consume menos recursos que **top**.

```bash
$ free
 total       used       free     shared    buffers     cached
Mem:       1019252      74600     944652          0       4952      50708
-/+ buffers/cache:      18940    1000312
Swap:            0          0          0
```

La línea **-/+** refleja el total de memoria principal dividido en base a la memoriausada por la cada una de estas dos últimas cantidades



#### 4.2. Orden *vmstat*

Sirve para supervisar el sistema mostrando información de memoria pero también acerca de procesos, E/S y CPU.

```bash
vmstat 2 20
procs -----------memory---------- ---swap-- -----io---- --system-- -----cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 0  0      0 944404   5000  50844    0    0     8     3  100    4  0  0 100  0  0	
 0  0      0 944404   5000  50844    0    0     0     0   99    4  0  0 100  0  0	
 0  0      0 944404   5000  50844    0    0     0     0   99    2  0  0 100  0  0	
 0  0      0 944404   5000  50844    0    0     0     0   99    2  0  0 100  0  0	
 0  0      0 944404   5000  50844    0    0     0     0   99    1  0  0 100  0  0	
 0  0      0 944404   5000  50844    0    0     0     0   99    5  0  0 100  0  0	
```

Las columnas muestran:

- **us:** Programas o peticiones del usuario
- **sy**: Tareas del sistema
- **id**: No haciendo nada en absoluto
- **r**: Cuántos procesos están en cola de ejecución
- **wa**: Indica que no hay procesos en espacio de intercambio
- **so**: Indicaría que se está incrementando el espacio de intercambio
- **free**: Indica que la memoria principal libre se está agotando



### 5. Control y gestión de dispositivos E/S

El SO necesita mantener una estructura de datos por cada archivo que contenga la información que le es necesario para poder trabajar con él. A esta información se le conoce comunmente como **metadatos de archivo**.

#### 5.1. Consulta de información de archivos

Vamos a profundizar sobre las opciones de la orden **ls**:

| Opciones   | Descripción                                                  |
| ---------- | ------------------------------------------------------------ |
| **ls -l**  | Imprime en fomato largo los metadatos de cada archivo        |
| **ls -n**  | Imprime lista numérica de ID de usuarios y grupos            |
| **ls -la** | Como ls -l, pero muestra también los archivos ocultos        |
| **ls -li** | Incluye el número del campo del inodo                        |
| **ls -lh** | Igual que -s -l, pero el tamaño de los archivos se imprimen en Kbytes, Mbytes o Gbytes |
| **ls -X**  | Ordena  alfabéticamente                                      |
| **ls -t**  | Ordena por tiempo de modificación                            |
| **ls -u**  | Ordena por tiempo de acceso                                  |
| **ls -c**  | Ordena por ctime                                             |

Los carácteres asociados a los tipos de archivos son:

- **-** : Archivo regular
- **d** : Directorio
- **l** : Enlace simbólico
- **b** : Archivo especial de dispositivo de bloques
- **c** : Archivo especial de dispositivo de caracteres
- **p** : Archivo FIFO para comunicaciones entre procesos

```bash
$ ls -lu
total 2280
-rw-r--r-- 1 1000 1000 359699 Oct 10 12:00 ORBit-0.5.17-25.fc11.i586.rpm
-rw-r--r-- 1 1000 1000 302712 Oct 10 12:00 ORBit-0.5.17-30.fc14.i686.rpm
-rw-r--r-- 1 1000 1000 126716 Oct 10 11:59 device-mapper-1.02.54-3.fc14.i686.rpm
-rw-r--r-- 1 1000 1000 134536 Oct 10 11:59 device-mapper-libs-1.02.54-3.fc14.i686.rpm

$ ls -lc
total 2280
-rw-r--r-- 1 1000 1000 359699 Oct 10 11:12 ORBit-0.5.17-25.fc11.i586.rpm
-rw-r--r-- 1 1000 1000 302712 Oct 10 11:12 ORBit-0.5.17-30.fc14.i686.rpm
-rw-r--r-- 1 1000 1000 126716 Oct 10 11:12 device-mapper-1.02.54-3.fc14.i686.rpm
-rw-r--r-- 1 1000 1000 134536 Oct 10 11:12 device-mapper-libs-1.02.54-3.fc14.i686.rpm
```



#### Actividad: Consulta de metadatos de archivo

Anota al menos dos nombres de archivo de dispositivo de bloques y dos nombres de dispositivo de caracteres de tu sistema UML. Anota los nombres de los archivos ocultos de tu directorio de inicio como usuario root que tienen relación con el intérprete de órdenes que tienes asignado por defecto. Ahora efectúa la misma tarea pero en una consola de terminal del sistema Ubuntu que arrancas inicialmente en el laboratorio de prácticas. ¿Qué diferencias encuentras entre los nombres de los archivos?

**PENDIENTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE**



#### 5.2. Consulta de metadatos del SA

Para poder asignar espacio en un disco, tanto para datos de archivo como para metadatos de archivo, los sistemas de archivo tipo UNIX/Linux mantienen información relativa a bloques de disco libres/ocupados e inodos libres/asignados.

La orden **df** permite visualizar información sobre su capacidad de almacenamiento total, el espacio usado en almacenamiento total, el espacio usado, el espacio libre y el punto de montaje en la jerarquía de directorios.

```bash
$ df
Filesystem           1K-blocks      Used Available Use% Mounted on
LABEL=ROOT             1032088    411180    568480  42% /
tmpfs                  1032088    411180    568480  42% /dev/shm
/tmp                    510244         0    510244   0% /tmp

# Usando la opción -i podemos visualizar la información sobre los inodos
$ df -i
Filesystem            Inodes   IUsed   IFree IUse% Mounted on
LABEL=ROOT             65536   14665   50871   23% /
tmpfs                  65536   14665   50871   23% /dev/shm
/tmp                  127561       2  127559    1% /tmp
```

Para porder ver el espacio en el disco que gasta un directorio de la jerarquía de directorios y todo sus subárboles, se usa la orden **du**. Hay que tener en cuenta:

- La última línea muestra por pantalla la cantidad total de bloques utilizadas por el subárbol
- Contabiliza los bloques asignados, estén o no ocupados

```bash
$ du home/
4	home/
```



#### Actividad: Metadaos del sistema 

Resuelve las siguientes cuestiones:

1. Comprueba cuántos bloques de datos está utilizando la partición raíz del sistema UML. Ahora obtén la misma información, pero en Megabytes o Gigabytes.

   ```bash
   $ du /
   377132	/	# Nos fijamos en la última línea
   
   # Para mostrar la salida en Gb o Mb
   $ du --block-size=1M #1G	# También puedes usar --human-readable o -h
   369	/
   ```

2. ¿Cuántos inodos se están utilizando en la partición raíz? ¿Cuántos nuevos archivos se podrían crear en esta partición?

   ```bash
   $ df -i /
   Filesystem            Inodes   IUsed   IFree IUse% Mounted on
   LABEL=ROOT             65536   14665   50871   23% /
   
   # Se podrían crear tantos como IFree hubiera
   ```

3. ¿Cuál es el tamañp del directorio /etc? ¿ Y el del directorio /var? Compara estos tamaños con los de los directorios /bin, /usr y /lib.

   ```bash
   $ du -h /etc/
   21M	/etc/	# Nos fijamos en la última línea
   
   $ du -h /bin/
   5.3M	/bin/
   
   $ du -h /usr/
   297M	/usr/
   
   $ du -h /lib/
   24M	/lib/
   ```

4. Obtén el número de bloques de tamaño 4KB que utiliza la rama de la estructura jerárquica de directorios que comienza en el directorio /etc.

   ```bash
   $ du -h /etc/ | grep 4.0K # Si queremos contar líneas wc -l
    du -h /etc/ | grep 4.0K
   4.0K	/etc/rwtab.d
   4.0K	/etc/chkconfig.d
   4.0K	/etc/rc.d/rc5.d
   4.0K	/etc/rc.d/rc1.d
   4.0K	/etc/rc.d/rc0.d
   4.0K	/etc/rc.d/rc6.d
   4.0K	/etc/rc.d/rc2.d
   4.0K	/etc/rc.d/rc4.d
   4.0K	/etc/rc.d/rc3.d
   ...
   ```



#### 5.3. Creación de enlaces a archivos

El objetivo de los enlaces de archivos es disponer de más de un nombre para los archivos en nuestro espacio de nombres de archivo soportado por la estructura jerárquica de directorios. 

Bajo esta óptica, los enlaces a  archivos pueden considerarse como referencia a otros archivos, bien a su nombre, **enlaces simbólicos**, bien a sus metadatos (acceso directo, con el distinto inodo al archivo que apunta, luego si eliminas el objeto inicial, no se puede acceder a los datos mediante en enlace simbólico), **enlaces duros** (Se establece sobre el mismo inodo, por tanto para eliminar el archivo hay que eliminar todos los enlacez duros. Si se modifica uno se modifican todos, ya que están sobre el mismo inodo) .

Podemos usar la orden **ls -la** para comprobar que todos los directorios tienen dos enlaces duros:

```bash
$ cd mnt/
$ ls -la 
ls -la
total 8
drwxr-xr-x  2 root root 4096 Apr 19  2010 .
dr-xr-xr-x 22 root root 4096 Oct 11 06:08 ..
```

Para crear enlaces duros o enlaces simbólicos sobre un archivo creado previamente se utiliza las orden **ln**. Como argumento básico debemos pasar el nombre del archivo a enlazar y el nuevo nombre.

```bash
$ touch archivo.txt
$ ln archivo.txt hardLink	
$ ln -s archivo.txt softLink # -s para softLink
$ ls -lai
total 8
  309 drwxr-xr-x  2 root root 4096 Oct 11 06:49 .
    2 dr-xr-xr-x 22 root root 4096 Oct 11 06:08 ..
14175 -rw-r--r--  2 root root    0 Oct 11 06:49 archivo.txt
14175 -rw-r--r--  2 root root    0 Oct 11 06:49 hardLink
14239 lrwxrwxrwx  1 root root   11 Oct 12 04:51 softLink -> archivo.txt
```

Los números que aparecen en la columna inmediatamente anterior al **username** son los valores del campo **contador de enlaces**, que antiene el número de enlaces duros a archivo con el objetivo de liberar el inodo cuando todos los nombres de archivo que utilizan dicho inodo hayan sido eliminados de la estructura de directorios.



#### Actividad: Trabajo con enlaces

Proporciona las opciones necesarias de la orden **ls** para obtener la información de metadatos de los archivos de un directorio concreto en los dos casos siguientes:

- En el caso de  que haya archivos de tipo enlace simbólico, la orden debe mostrar la información del archivo al que enlaza cada enlace simbólico y no la del propio archivo de tipo enlace simbólico

  ```bash
  $ ls -laiL
  total 32
    311 dr-xr-x---  2 root root 4096 Oct 12 04:51 .
      2 dr-xr-xr-x 22 root root 4096 Oct 12 04:47 ..
     58 -rw-------  1 root root   53 Sep 13  2011 .bash_history
   3958 -rw-r--r--  1 root root   18 Mar 30  2009 .bash_logout
   3959 -rw-r--r--  1 root root  176 Mar 30  2009 .bash_profile
   3960 -rw-r--r--  1 root root  176 Sep 22  2004 .bashrc
   3961 -rw-r--r--  1 root root  100 Sep 22  2004 .cshrc
   3962 -rw-r--r--  1 root root  129 Dec  3  2004 .tcshrc
  14175 -rw-r--r--  2 root root    0 Oct 12 04:49 archivo.txt #######
  14175 -rw-r--r--  2 root root    0 Oct 12 04:49 hardLink
  14238 -rw-r--r--  2 root root    0 Oct 12 04:49 hardLink2
  14175 -rw-r--r--  2 root root    0 Oct 12 04:49 softLink #######
  14238 -rw-r--r--  2 root root    0 Oct 12 04:49 target_hardLinj.txt
  ```

- En el caso de enlaces simbólicos debe mostrar la información del enlace en sí, no del archivo al cual enlaza. En el caso de directorios no debe mostrar su contenido sino los metadatos del directorio.

  ```bash
  # Para la primera parte se usa como siempre ls -lai. Para la segunda:
  $ ls -laid
  311 dr-xr-x--- 2 root root 4096 Oct 12 04:51 .
  ```



#### 5.4. Archivos especiales de dispositivo

Los dispositivos de nuestro sistema se representan mediante archivos especiales de dispositivo, que pueden ser de bloques o de caracteres. Los archivos especiales de bloque  representan  a dispositivos   debloques, que normalmente coinciden con los dispositivos de almacenamiento persistente, losramdisks y los dispositivos loop. Los archivos especiales de caracteres representan a dispositivosde caracteres del tipo puertos serie, paralelo y USB, consola virtual (console),  audio, losdispositivos de terminal (tty*), y muchos más

```bash
$ ls -l /dev
total 12
crw------- 1 root root 5, 1 Oct 12 04:47 console
crw-rw-rw- 1 root root 1, 7 Nov  3  2010 full
-rw-r--r-- 1 root root   54 Sep 13  2011 kmsg
srw-rw-rw- 1 root root    0 Oct 12 04:47 log
drwxr-xr-x 2 root root 4096 Nov  3  2010 mapper
crw-rw-rw- 1 root root 1, 3 Nov  3  2010 null
crw-rw-rw- 1 root root 5, 2 Nov  3  2010 ptmx
drwxr-xr-x 2 root root    0 Oct 12 04:47 pts
crw-rw-rw- 1 root root 1, 8 Nov  3  2010 random
drwxr-xr-x 2 root root 4096 Nov  3  2010 shm
lrwxrwxrwx 1 root root   15 Nov  3  2010 stderr -> /proc/self/fd/2
lrwxrwxrwx 1 root root   15 Nov  3  2010 stdin -> /proc/self/fd/0
lrwxrwxrwx 1 root root   15 Nov  3  2010 stdout -> /proc/self/fd/1
crw-rw-rw- 1 root root 5, 0 Nov  3  2010 tty
crw--w---- 1 root tty  4, 0 Oct 12 05:07 tty0
cr--r--r-- 1 root root 1, 9 Nov  3  2010 urandom
crw-rw-rw- 1 root root 1, 5 Nov  3  2010 zero
```

Podemos crear archivos especiales usando la orden **mknod**. Permite especificar el nombre del archivo y los números principales (**major**) y secundario (**minor**), lo cual  permite identificar a los dispositivos en el kernel. El número principal determina el controlador al que está conectado el dispositivo y el número secundario al dispositivo en sí.



#### Actividad: Creación de archivos especiales

Crear un dispositivo de bloques y otro de caracteres y proporciona una salida ls -li de los dos archivos de dispositivo recién creados.

```bash
# Para un dispositivo de bloques
$ mknod dispbloques b 10 5

# Para crear un dispositivo de caracteres
$ mknod dispcaracteres c 10 5

$ ls -li
14241 brw-r--r-- 1 root root 10, 5 Oct 12 05:17 dispbloques
14248 crw-r--r-- 1 root root 10, 5 Oct 12 05:18 dispcaracteres
```



## **<u>Sesión 4</u>**

En esta sesión veremos como lanzar órdenes cuya ejecución se realice en un determinado momento de tiempo o de forma periódica.

El administrador del sistema será el responsable del buen funcionamiento de estos servicios del sistema operativo: el demonio **atd** (proporciona el servicio de ejecución postergada de órdenes) y el demonio **cron** (que proporciona el servicio de ejecución periódica de órdenes)



### 3.Los procesos demonios

Características de un proceso demonio:

	17. Se ejecuta en background y no está asociado a un terminal o proceso login
 	18. Algunos se inician en el arranque del sistema y continúan ajecutándose mientras el sistema está encendido, otros solo se ponen en marcha cuando son necesarios
 	19. En caso de que termine por algún imprevisto es muy común que exista un mecanismo que detecte la terminación y lo rearranque.
 	20. En muchos casos está a la espera de un evento
 	21. En otros casos, tiene encomendada una labor que hay que hacer de forma periódica
 	22. Es frecuente que no hagan el trabajo directamente, sino que lanza otros procesos para que lo realicen
 	23. En muchos casos se ejecutan con privilegio de superusuario (UID=0)  y tienen por padre al proceso **init** (PID=1)



#### Actividad: Consulta de información sobre procesos demonio

A partir de la información proporcionada por la orden **ps** encuentre los datos asociados a los demonios **atd** y **crond**, en concreto: quién es su padre, qué terminal tiene asociado y cuál es su usuario.

```bash
$ ps -ef | grep cron; ps -ef | grep atd
UID          PID    PPID  C STIME TTY          TIME CMD
daemon      8170       1  0 09:07 ?        00:00:00 /usr/sbin/atd -f
daniel      9862    7533  0 09:14 pts/1    00:00:00 grep --color=auto atd
root        1010       1  0 08:12 ?        00:00:00 /usr/sbin/cron -f
daniel      9864    7533  0 09:14 pts/1    00:00:00 grep --color=auto cron

# El UID es el id del usuario
# TTY es la terminal asociada (? significa que no tiene una asociada)
# PPID es la id del proceso padre
```



### 4. Ejecutar tareas a una determinada hora: demonio *atd*

Con el demonio **atd** podemos provocar la ejecución de una orden en un momento de tiempo especificado. Podemos usar las siguientes ódenes:

- **at**: Ejecuta una órden a una determiada hora
- **atq**: Consulta la lista de órdenes
- **atrm**: Elimina órdenes
- **batch**: Ordena la ejecución de órdenes que se ejecutarán cuando la carga del sistema sea baja



#### 4.1. Orden *at*

Su sintaxis completa es:

```bash
$ at [-q queue] [-f <script>] [-mldbv] Time
```

La orden **at** lee órdenes de la entrada estándar o del archivo <script> y provoca su ejecución a la hora especificada. Para ver las posibles hora de expresar time vease el contenido del archivo **/usr/share/doc/at/timespec**



#### Actividad: Ejecución postergada de órdenes con *at*

Crea un archivo **genera-apunte** que escribe la lista de hijos del directorio home en un archivo de nombre **listahome-`date +Y-%-%j-%T-$$**, es decir, la yuxtaposición del literal "listhome" y el año, día dentro del año, la hora actual y el pid.

Lanza la ejecución del archivo **generate-apunte** un minuto más tarde de la hora actual.

```bash
$ touch generate-apunte.sh
$ chmod +x generate-apunte.sh
$vi generate-apunte.sh
#!/bin/bash

ls ~ > listahome-`date +%Y-%j-%T-$$`

$ at now + 1minute
at> ./generate-apunte.sh

#También podemos $ at -f ./generate-apunte.sh 9:02
```

¿En qué directorio se crea el archivo de salida?

```
En la carpeta donde la ejecutammos
```



#### Actividad: Ejecución postergada de órdenes con *at*

Lanza varias órdenes **at** utilizando distintas formas de especificar el tiempo como las siguientes (será de utilidad con la opción -v):

a) a medianoche de hoy

```bash
$ at midnight
$ at 00:00
```

b) un minuto después de la medianoche de hoy

```bash
$ at midnight +1 minute
```

c) a las 17 horas y 30 minutos de mañana

```bash
$ at 17:30 +1 day
$ at 17:30 tomorrow
```

d) a la misma hora en que estemos ahora pero del día 25 de diciembre del presente año

```bash
$ at 25.12.2020
```

e) a las 00:00 del presente año

```bash
$ at 00:01 01.01.2021
at: refusing to create job destined in the past
```



#### 4.2. Sobre el entorno de ejecución de las órdenes

Cuando sea el momento que se especificó en la orden **at** se lanzará una shell **/bin/sh** para ejecutar el archivo <script> que se indicó (o si no se especificó, se lanza el conjunto de ordenes que se tomaron de la entrada estándar); podemos preguntarnos sobre cuál es el entorno de este nuevo proceso. Para ello véase la siguiente actividad:



#### Actividad: Cuestiones sobre *at*

El proceso nuevo que se lanza al cumplirse el tiempo especificado:

1. ¿Que directorio de trabajo tiene inicialmente? ¿Hereda el que tenía el proceso que invocó a at o bien es home?

   ```
   Hereda el directorio del proceso que se invocó a at
   ```

2. ¿Qué máscara de creación de archivos umask tiene? ¿es la que hereda del padre o la que se usa por omisión?

   ```
   La hereda del padre desde el momento de la invocación
   ```

3. ¿Hereda las variables del proceso padre?

   ```
   El entorno se mantiene desde la invocación, pero no las variables
   ```



#### Actividad: Relación padre-hijo con órdenes ejecutada mediante *at*

El proceso nuevo que se lanza al cumpirse el tiempo que se especificó de la orden **at**, ¿de quién es hijo? Investiga lanzando la ejecución retardada deun script que muestre la inforación completa sobre los procesos existentes y el pid del proceso actual; el script es el siguiente:

```bash
#!/bin/bash

nombrearchivo=`date +%Y-%j-%T`
ps -ef > $nombrearchivo
echo Mi pid == $$ >> $nombrearchivo
```

Ejecutamos la script anterior:

```bash
$ at -f ./script.sh now + 1minute
warning: commands will be executed using /bin/sh
job 7 at Tue Oct 20 13:54:00 2020

# Veamos el resultado
$ cat 2020-294-13\:54\:00 
UID          PID    PPID  C STIME TTY          TIME CMD
root           1       0  0 08:12 ?        00:00:12 /sbin/init splash
root           2       0  0 08:12 ?        00:00:00 [kthreadd]
root           3       2  0 08:12 ?        00:00:00 [rcu_gp]
root           4       2  0 08:12 ?        00:00:00 [rcu_par_gp]
root           6       2  0 08:12 ?        00:00:00 [kworker/0:0H-kblockd]
root           9       2  0 08:12 ?        00:00:00 [mm_percpu_wq]

...
```



#### 4.3. Salida estándar y salida de error estándar

Al lanzar una ejecución asíncrona de una tarea con la orden **at** NO estamos creando un proceso hijo en nuestra shell, por lo que no tendrá ni entrada ni salida estándar ni entrada ni salida de error.

Cuando la orden lanzada de forma retardada sea ejecutada, lo que genere la salida estándar y la salida de error estándar se envía al usuario que envión la orden como  un correo electrónico usando la orden **/usr/bin/sendmail.**

En el caso delanzar la ejecución de órdenes que generan muchos mensajesen la salida estándar o salida de error estándar podríamos registrarlas a **/dev/null** para que se "pierda":

```bash
$ at now +1 minute
at> tarcvf /backups/backup.tar . l>> ~/salidas 2> /dev/null
```

También puede ser conveniente rederigir directamente la salida. Si ejecutamos las ordenes sin estas medidas y da error, no seremos notificados y pasará desapercibido.



#### Actividad: Script para orden *at*

Construye un script que utilice la orden **find** para generar la salida estándar de los archivos modificados en las últimas 24 horas (partiendo de home y de forma recursiva). La salida deberá escribirse en el archivo "modificados_< año >< dia >< hora >". Utiliza la orden **at** para que se ejecute dentro de un día

```bash
$ touch script.sh
$ vi script.sh
#!/bin/bash

find . -mtime 1 > modificados_`date +%Y-%j-%T`

$ chmod +x script.sh
$ at now + 1day
at> ./script.sh

# También se puede at -f ./script.sh
```



#### 4.4. Orden *batch*

La orden **batch** es equivalente a **at** excepto que no especificamos la hora de ejecución, sino que el trabajo especificado se ejecutará cuando la carga de trabajos del sistema esté bao cierto valor umbral que se especifica a la hora de lanzar el demonio **atd**



#### Actividad: Trabajo con la orden *batch*

Lanza los procesos que sean necesarios para conseguir que exista una gran carga de trabajo en el sistema de modo que los trabajos lanzado con la orden **batch** no se estén ejecutando. Utiliza las órdenes oportunas para matar este conjunto de procesos. Experimenta para comprobar como al ir bajando la carga de trabajos habrá un momento en que se ejecutan los trabajos lanzados a la cola batch.

**Pendiente**



#### 4.5. Orden *at* trabajando con colas

La orden **at** gestiona distintas colas de trabajos que esperan ser ejecutados; se designan con una única letra de la **a** a la **z** y de la **A** a la **Z**. La columna por omisión es **a**, la cola **b** se usa para batch y a partir de ahí las distintas colas van teniendo menor prioridad de la **c** en adelnate.



#### Actividad: Utilizando las colas de trabajos de *at*

Construye tres scripts que deberás lanzar a las colas **c,d,e** y especificando una hora concreta que esté unos pocos minutos más adelante. Idea qué actuación deben tener dichos script de forma que se ponda de manifiesto que de esas colas la orden más prioritaria es la **c** y la que menos es la **e**.

```bash
# Usemos por ejemplo la script anterior
#!/bin/bash

nombrearchivo=`date +%Y-%j-%T`
ps -ef > $nombrearchivo
echo Mi pid == $$ >> $nombrearchivo

$ at -q c -f ./script.sh now + 1minute
$ at -q d -f ./script.sh now + 1minute
$ at -q e -f ./script.sh now + 1minute
```

Veamos las prioridades:

```bash
$ atq -q c
29Mon Oct 29 13:11:00 2012 c superjes
$ atq -q d
30Mon Oct 29 13:11:00 2012 d superjes
$ atq -q e31
Mon Oct 29 13:11:00 2012 e superjes
```

Usando ls en el directorio, efectivamente vemos que se ha ejecutado primero la cola c, luego la d y, por último, la d.



#### 4.6. Aspectos de administración del demonio *atd*

Los dos archivos de configuración **/etc/at.deny** y **/etc/at.allow** determinan los usuarios del sistema que pueden usar la orden at.



### 5. Ejecuciones periódicas: demonio cron

El demonio **cron** es responsable de ejecutar órdenes con una periocidad determinada. La especificación de las tareas que se desea que ejecute se hace constuyendo un archivo, que deberá tener un determinado formato, que se pasa comunica con el demonio mediante la orden **crontab**.

#### 5.1. Formato de los archivos crontab: especificando órdenes

Cada línea de código de un archivo cronta puede contener estos campos:

​							**minuto	hora	día-del-mes	mes	día-de-la-semana	orden**

Menos el último campo, todos indican la periocidad con la que se ejecuta una orden. A su vez, estos campos pueden contener:

- Un asterisco, que indica cualquier valor posible
- Un número entero, que activa ese valor determinado
- Dos enteros separados por un guión, que indican un rango de valores
- Una serie de enteros o rangos separados por una coma, activando cualquier valos que aparece en la lista

Por ejemplo **1 20 * * 1-5**, significa que se ejecuta a las 20:01 todos los días de lunes a viernes.

Si se indica valores concretos para los campos día-del-mes y  día-de-la-semana se entenderá como una orden **OR**, por ejemplo **0,30 * 13 * 5** significa cada media hora de los viernes y cada media hora del día 13 del mes.

#### 5.2. La orden *crontab*

Se encarga de instalarm desinstalar o listar los trabajos que procesará el demonio cron.

```bash
$ crontab <file>
```



#### Actividad: Relación padre-hijo con órdenes ejecutadas mediante crontab

Lanza un script como la de la actividad de la orden *at* sobre quién es el proceso padre del nuestro, lanza el script construido en dicha actividad con una periocidad de un minuto y analiza los resultados.

```
Lo mismo que ocurría con at, pero con el demonio cron
```



#### Actividad: Ejecución de scripts con *crontab*

Construye un script que sea lanzado con una periocidad de un minuto y que borre los nombres de los archivos que cuelguen del directorio **/tmp/varios** y que comiencen por "core" (cree ese directorio y algunos archivos para poder realizar esta actividad). Utiliza la opción **-v** de la orden **rm** para generar como salida una frase de confirmación de los archivos borrados; queremos que el conjunto de estas salidas se añadan al archivo **/tmp/listacores**.

Prueba la orden **crontab -l** para ver la lista actual de trabajos (consulte la ayuda para ver las restates posibilidades de esta orden para gestionar la lista actual de trabajos).

```bash
$ mkdir /tmp/varios
$ cd /tmp/varios
$ touch core.txt core1 core2 hola.txt noborrar.txt
$ cd ~
$ touch script.sh
$ chmod +x script.sh
$ vi script.sh
```

La script será la siguiente:

```bash
#!/bin/bash

rm -v /tmp/varios/core* >> /tmp/listacores
```

Lo añadimos al archivo crontab:

```bash
$ sudo service cron start	# Por si estuviera deshabilitado
$ contab -e	# Se abrirá un archivo editable, en el que añadimos la siguiente línea
* * * * * /home/daniel/script.sh
$crontab -l	# Veremos que se ha añadido a la listas de tareas a ejecutar
...
* * * * * ./home/daniel/script.sh
```

Para eliminar la tarea, simplemente hay que modificar nuevamente el archivo



#### Actividad: Ejecución de scripts con *crontab (II)*

Para asegurar que el contenido del archivo **/tmp/listacores** no crezca demasiado, queremos que periódicamente se deje dicho archivo solo con sus 10 primeras líneas  (puede ser de utilidad la orden **head**). Construye un script llamado **reducelista** que realice la función anterior y la ejecute con una periocidad de un minuto.

La script en cuestión será:

```bash
#!/bin/bash

head -n 10 /tmp/listacores > /tmp/listacores1
rm /tmp/listacores1
mv /tmp/listacores1 /tmp/listacores
```

Repetimos los pasos del ejercicio anterior:

```bash
$ touch script2.sh
$ vi script2.sh
$ chmod +c script2.sh
$ crontab -e 
* * * * * /home/daniel/script2.sh
$ crontab -l	# Veremos que se ha añadido
```



#### Actividad: Ejecución de scripts con *crontab (III)*

Construye una script que escriba en el archivo **listabusqueda** una nueva línea con la fecha y hora actual y después el valor de la lista de búsqueda, por ejemplo:

​		...

​		2011-297-12:29:10 - /usr/local/bin: /usr/local/bin: /usr/bin...

​		...

Ejecuta  esta script desde el lenguaje de órdenes y también lánzalo como trabajo crontab y compara los resultados, ¿se tiene en ambos casos la misma lista de búsqueda?

```bash
$ touch script3.sh
$ chmod +x script3.sh
$ vi script3.sh
#!/bin/bash

fecha=`date +%Y-%j-%T`

echo $fecha - $PATH >> /home/daniel/listabusqueda
$ crontab -e
PATH=/usr/local/bin:/usr/local/bin:/usr/bin...
* * * * * /home/daniel/script3.sh
$ cat listabusqueda
2020-299-22:15:01 - /usr/local/bin:/usr/local/bin:/usr/bin...
```



#### 5.3. Formato de los archivos crontab: especificando variables de entorno

Una línea de un archivo crontab puede ser o bien una línea de especificación de una orden para cron o bien una línea de asignación de variables de entorno (**< nombre >=< valor >**).

Algunas variables de entorno son establecidas automáticamente por el demonio  cron, como las siguientes:

- **SHELL**: se establece a **/bin/sh**
- **LOGNAME** y **HOME**



#### Actividad: Variables de entorno en archivos *crontab*

Construye un script que generará un archivo crontab llamado **crontab-reducelista** que deberá contener:

- Como primera línea de asignación a la variable PATH de la lista de búsqueda actual y además el directorio $HOME/SO
- La indicación a cron de la ejecución con periocidad de 1 minuto del script **reducelista**

Una vez construido **crontab-reducelista**, lánzalo con la orden crontab. Comprueba que con esta nueva lista de búsqueda podremos hacer alusión a **reducelista** especificando únicamente su nombre independientemente del directorio de trabajo donde nos situemos.

El script será el siguiente:

```bash
#!/bin/bash

echo "SHEL=/bin/bash" > crontab-reducelista
echo "PATH="`pwd`" /:$HOME/SO:"$PATH >> crontab-reducelista
echo "* * * * * reducelista" >> crontab-reducelista
```

Lanzando el script tenemos:

```bash
$ vi crontab-reducelista
SHEL=/bin/bash
PATH=/home/daniel /:/home/daniel/SO:/home/daniel/.local/bin:/usr/local/sbin:/us>
* * * * * reducelista
$crontab crontab-reducelista
```



#### Actividad: Archivos *crontab* de diferentes usuarios

Vamos a lanzar un archivo crontab cuyo propietario es otro usuario. Visualiza el contenido del archivo **/fenix/depar/lsi/so/ver-entorno** y **/fenix/depar/lsi/so/crontabver**. Comprueba con **ls -l** que propietario es el usuario del **lsi**. Sin copiarlos, úsalos para lanzar la ejecución cada minuto del script  **/fenix/depar/lsi/so/ver-entorno**. Analiza el archivo de salida: ¿de qué línea del archivo **/etc/passwd** se toma **LOGNAME** y **HOME** de la línea del propietario del archivo crontab o de la línea del usuario que lanza el archivo crontab?

**Pendiente**



#### Actividad: Ejecución de scripts *crontab (IV)*

El objetivo es ejecutar todos los días a las 0 horas 0 minutos una copia de los archivos que cuelguen de **$HOME** que se hayan modificado d¡e las últimas 24 horas. Vamos a programar este salvado incremental utilizando la orden **find**, pero ahora queremos que se copien los archivos encontrados utilizando la orden **cpio:**

​		**< orden find > | cpio -pmduv  /tmp/salvado$HOME**

Comenzamos creando el script:

```bash
#!/bin/bash

find ~ -mtime 1 | cpio -pmduv /tmp/salvado$HOME
```

Se lo pasamos a crontab:

```bash
$ touch script5.sh
$ chmod +x script5.sh
$ vi script5.sh	# Creamos el script
$ crontab -e 
0 0 * * * /home/daniel/script5.sh
$ crontab -l # Comprobamos que se ha añadido a la lista
```



Una característica interesante de esta orden, que no tiene cp, es que puede tomar de la entrada estándar los archivos origen a copiar.  Con las opciones anteriores, permite replicar la estrucutura original manteniendo metadatos de especial interés como usuario propietario y grupo propietario.

Esto puede ser una labor interesante de programar para un administrador de sistemas, con objeto de tener una copia de los archivos que se han modificado. Por ejemplo un vez al mes se puede hacer un salvado global, y una vez al día un salvado de los archivos modificados.

Una posibilidad interesante es que la copia de seguridad se haga en un dispositivo que acabamos de montar, y, justo al desmontar, lo desmontamos. Esto aumenta la posibilidad de la copia ante posibles ataques:

​		**mount /dev/loop0	/directoriosalvados**

​		**< orden find > | < orden cpio >**

​		**unmount /dev/loop0**

Como última observación, si el dispositivo y punto demontaje usados en esa orden mount, no están en el fstab serán más difíciles de detectar por un intruso que acceda a nuestro sistema.



#### 5.4. Aspectos de administración del demonio crontab

Los dos archivos de configuración **/etc/cron.deny** y **/etc/cron.allow** determinan qué usuarios pueden ejecutar la orden crontab. Su significado es equivalente a los archivos **/etc/at.deny** y **/etc/at.allow**



#### Actividad: Gestión de servicio *crond* como usuario root

Prueba las siguientes operaciones con el demonio **crond**:

1. Como usuario root, deshabilita/habilita a un determinado usuario para que pueda utilizar el servicio cron; comprueba que efectivamente funciona.

2. Iniciar y terminar el servicio cron. Prueba las siguientes órdenes para iniciar y terminar este servicios:

   ​	Iniciar el servicio cron: **/sbin/service crond start**

   ​	Terminar el servicio cron: **/sbin/service crond stop**

```bash
# Añadimos un usuario en /etc/cron.deny
$ echo prueba >> /etc/cron.deny
# Accedemos al usuario
$ su prueba
# Probamos a usar cron
You (prueba) are not allowed to use this program (crontab)See crontab(1) for more information
```

