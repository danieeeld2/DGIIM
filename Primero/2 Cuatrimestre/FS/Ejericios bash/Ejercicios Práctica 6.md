##### Ejercicios Práctica 6

**1.- Usa uno de los guiones que tienes y ejecútalo en background**

```bash
#Para ello usamos el metacarácter &
nombredelguion &
```

**2.- Indica el número del proceso asignado**

```bash
$bash prueba &
[1] 6977 #Nos indica el número del  proceso y el ID
```

**3.- ¿Cómo matarías a dicho proceso antes de finalizar?**

```bash
kill 6977
```

**4.- Muestra la información más completa de todos los procesos que se estén ejecutando en el sistema (no solo los tuyos)**

Primera opción: 

```bash
ps -el
```

Segunda opción: 

```bash
top
```

