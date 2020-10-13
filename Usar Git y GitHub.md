# Apuntes de Git y GitHub

###### Daniel Alconchel Vázquez

------

Git es un un sistema de control de versiones (VCS), es decir, permite gestionar las distintas versiones de un proyecto. Permite ir controlando el desarrollo del proyecto, así como trabajar de forma coperativa con otras personas.



Para comenzar vamos a configurar git:

```bash
$git config --global user.email "youremail"
$git config --global user.name "Tu nombre"
```



Para comenzar, imaginemos que tenemos un nuevo proyecto **~/Proyecto**. Para iniciar un git del proyecto:

```bash
$ cd ~/Proyecto
$ git init

# Se te creará una carpeta oculta llamada .git
```

Para ver con que archivos estamos trabajando ejecutamos:

```bash
$ git status
```

Te saldrá una lista de archivos en rojo, lo cual significan que no estan siendo seguidos por git. Para añadirlos:

```bash
$ git add <file> 
$ git add . # Si quieres añadir todos los archivos de un directorio
```

Si ahora volvemos a hacer **git** **status**, aquellos archivos que hayamos añadidos saldrán en una lista en verde, pero no están publicados:

```bash
$ git commit -m 'Escribe aquí un mensaje'
```

Si queremos que algún archivo o carpeta sea ignorado creamos el archivo **.gitignore** y en dicho archivo añadimos lo que queremos ignorar.



Si actualizamos algunos de los archivos que ya teníamos  subidos  podemos ver los cambios realizados usando:

```bash
$ git diff <file>

# Agregamos nuevamente los cambios:
$ git add <file> 
$ git commit -m 'Escribe aquí un mensaje'
```

Si usamos el siguiente comando, podemos ver las distintas versiones:

```bash
$ git log
```



Imaginemos que queremos tener versiones alternativas de un proyecto, entonces podemos crear varias ramas usando el siguiente comando:

```bash
$ git branch <nombrederama>
```

Para ver en que rama estoy y cambiar entre ramas:

```bash
$ git branch # Devuelve la rama en la que te encuentras
$ git checkout <nombrederama>	# Cambia de rama
```



Para enlazar el git a la plataforma github, entramos a la web, iniciamos sesión y creamos un nuevo repositorio. Ahora podemos almacenar todo el código que hemos estado trabajando usando el comando sobre la carpeta del proyecto git:

```bash
$ git remote add origin <direccionwebasignada>
```

Para publicar en la web, simplemente ejecutamos el siguiente comando:

```bash
$ git push -u origin <rama>
```

En github podemos añadir archivos markdown, por defectos llamados README, los cuales permiten explicar a los usuarios como funciona tu proyecto.



Si hemos eliminado todo el código de nuestro ordenador y queremos recuperarlo, solo necesitamos ir a GitHub, copiar la direción web del proyecto y ejecutar:

```bash
$ git clone <direccion>
```

Esto descargará el proyecto