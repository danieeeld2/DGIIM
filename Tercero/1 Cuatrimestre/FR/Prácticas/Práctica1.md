# Fundamentos de Redes

## Práctica 1

###### Daniel Alconchel Vázquez

#### 1. Objetivo

El objetivo de esta práctica es introducir al alumnado a la configuración de rutas de encaminamiento tanto estáticas, como dinámicas.

#### 2. Estructura del Aula

![](https://github.com/danieeeld2/DGIIM/blob/master/Tercero/1%20Cuatrimestre/FR/Pr%C3%A1cticas/.Imagenes/Captura%20de%20pantalla%20de%202021-10-13%2018-20-09.png)

![](https://github.com/danieeeld2/DGIIM/blob/master/Tercero/1%20Cuatrimestre/FR/Pr%C3%A1cticas/.Imagenes/Captura%20de%20pantalla%20de%202021-10-13%2018-20-32.png)

A partir de aquí, la *X* corresponde al número de la isla en la que se encuentra y la *Y* al número del dispositivo dentro de la red.

#### 3. Configuración de los routers

En todo momento podemos comprobar las direcciones IP que tienen asignadas las diferentes interfaces de red de nuestro puesto mediante el comando 

```bash
ifconfig
```

##### 3.1. Configuración de las tablas de enrutamiento (Encaminamiento Estático)

###### En los Routers

La configutación de la tabla de enrutamiento mediante Telnet se puede llevar a cabo desde el menu ip del router. A continuación se muestra un ejemplo de configuración vía Telnet de una entrada en la tabla de encaminamiento del router *R1_1* que indica que todos los paquetes dirigidos a la subred *33.1.2.0/24* se encaminen por el router correspondiente, en este caso, el *R1_3*

```bash
$ sudo su
$ telnet <direccion IP de gestión del router>
[] ip
[] /ip route
[] /ip route> add dst-address=33.1.2.0/24 gateway=172.16.1.2
[] /ip route> print
```

###### En los puestos de usuario

Desde una terminal LINUX, la introducción de entradas en la tabla de enrutamiento puede realizarse de dos maneras:

- Mediante el comando **route**. En este caso la configuración no se mantiene al reiniciar el sistema:

  - Para añadir una entrada en la tabla de encaminamiento que indique que para llegar a cualquier IP que pertenezca a la subred *192.168.128/25* hay que reenviar el datagrama a la pasarela *192.168.1.2*:

    ```bash
    route add -net 192.168.1.128 netmask 255.255.255.128 gw 192.168.1.2
    ```

  - Para añador 192.168.1.200 como pasarela por defecto:

    ```bash
    route add default gw 192.168.1.200
    ```

- Escribiendo las entradas en el fichero **/etc/network/interfaces**. En este caso la configuración se mantendrá al reiniciar el sistema.

![](https://github.com/danieeeld2/DGIIM/blob/master/Tercero/1%20Cuatrimestre/FR/Pr%C3%A1cticas/.Imagenes/photo_2021-10-13_18-14-00.jpg)

![](https://github.com/danieeeld2/DGIIM/blob/master/Tercero/1%20Cuatrimestre/FR/Pr%C3%A1cticas/.Imagenes/photo_2021-10-13_18-14-21.jpg)

##### 3.2. Encaminamiento dinámico (RIP)

Para ello necesitamos eliminar todas las tablas de encaminamiento estático de la sección anterior.

Para configurar el RIP en todos y cada uno de los routers basta con ejecutar:

```bash
$ sudo su
$ telnet <direccion IP de gestión del router>
[] routing
[] /routing rip
[] /irouting rip> network add network=<dir. de red/mascara>
```

![](https://github.com/danieeeld2/DGIIM/blob/master/Tercero/1%20Cuatrimestre/FR/Pr%C3%A1cticas/.Imagenes/photo_2021-10-13_18-14-42.jpg)

![](https://github.com/danieeeld2/DGIIM/blob/master/Tercero/1%20Cuatrimestre/FR/Pr%C3%A1cticas/.Imagenes/photo_2021-10-13_18-14-45.jpg)

Si quisiéramos deshabiitar la interfaz de alguno de los routers:

```bash
$ sudo su
$ telnet <direccion IP de gestión del router>
[] interface
[] /interface> disable <nombre de la interfaz>
```

