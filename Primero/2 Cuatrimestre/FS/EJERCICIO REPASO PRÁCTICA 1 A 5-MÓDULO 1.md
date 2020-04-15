## EJERCICIO REPASO PRÁCTICA 1 A 5-MÓDULO 1

**1.-** Cree tres directorios con una única orden: **curso_1920** y dentro de éste, **cuatrimestre_1** y **cuatrimestre_2**

```bash
mkdir curso_1920; cd curso_1920; mkdir cuatrimestre_1 cuatrimestre_2

```

**2.- Cree** un archivo cuyo nombre sea **repasoMod1** en el directorio **curso_1920**. A continuación, **edítelo** y escriba lo siguiente:

DNI: *número del DNI*

Nombre y apellidos: *nombre y apellidos*

​	Fecha: *fecha actual(dd/mm/aaaa)*

```bash
cd ~; cd /curso_1920; touch repasoMod1; nano repasoMod1

#Desde el editor escribimos los datos anteriores y para guardar y salir crtl+X
```

**3.-** Copie el archivo **repasoMod1** del directorio curso_1920 en el directorio **cuatrimestre_1.**

```bash
#Desde el directorio en cuestión
cp RepasoMod1 ~/curso_1920/cuatrimestre_1
```

**4.-** Redireccione el resultado de ejecutar la orden que obtiene la fecha actual al fichero que ha creado en el punto 2 (en el directorio curso_1920) sin destruir su contenido.

```bash
date >> ~/curso_1920/RepasoMod1 
```

**5.-** Indique qué es necesario hacer para crear una variable RUTA que contenga la ruta absoluta del directorio en el que nos encontramos. Compruebe con el comando correspondiente las variables locales de su sistema.

```bash
$ruta=`pwd`
$set #Para mirar las variables locales
```

**6.-** Obtenga las 20 últimas lineas del manual de la orden find y guárdelas en un fichero llamado **ayudafind**, dentro del directorio **cuatrimestre_2.**

```bash
#Ya dentro del directorio en cuestión
$touch ayudafind; (man man find | tail -20) > ayudafind
```

**7.-**En la carpeta personal, construya un guión llamado **repaso-guion** que admita tres argumentos, el primero será un directorio, el segundo una letra, y el tercero una palabra:

​	examen-guion<nombre_directorio> <letra> <palabra>

El guión debe:

-Comprobar que se le están pasando tres argumentos, y si no fuera así, indicar cómo se debe ejecutar para que funcione correctamente. Esto es, dar una pequeña ayuda y terminar.

-Crear, en caso de no existir, el directorio dado como primer argumento.

​	-Comprobar que el segundo argumento sea una **f** o una **d**.  Si no fuera así, indicarlo con un mensaje de error y salir.

-Encontrar la palabra dada en el **tercer** argumento de forma recursiva en los archivos existentes a partir del directorio indicado por el usuario (**primer** argumento), incluyendo el número de línea en donde se localiza el término. Almacenar el resultado de la consulta en un fichero llamado **resultado** dentro del directorio desde el que se ejecute el guión.

-Buscar en el directorio indicado por el usuario (**primer** argumento) todos los ficheros o directorios según la letra pasada como **segundo** argumento (f=fichero, d=directorio) Almacenar el resultado de la consulta al final del fichero **resultado** del apartado anterior.

```bash

```

