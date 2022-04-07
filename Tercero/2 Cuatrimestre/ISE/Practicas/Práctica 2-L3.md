# ISE Práctica 2

## Lección 3

Hoy vamos a instalar una pila LAMP (Linux Apache MySQL PHP). Cuando te conectas a una página web, pides el index.html y te devuelve un string enorme que el navegador interpreta y dibuja.

Comenzamos  en Ubuntu instalando:

```bash
sudo apt install tasksel
sudo tasksel
```

Al ejecutarlo, nos sale una lista de software a instalar. Desmarcamos todos y marcamos solo `LAMP server`.

Ahora vemos si existe todo lo que necesitamos:

```bash
sudo systemctl status apache2
sudo systemctl start apache2
sudo systemctl status mysql
sudo systemctl start mysql
php -a # Para ver que esta la consola de php
```

Si escribimos la IP de ubuntu, que recordemos que es `192.168.56.105`, vemos que nos sale una página web. En esa página nos dice donde está alocado en `/var/www/html/index.html`. Podemos modificar este fichero y, al recargar la página, nos saldrán las modificaciones.

Si no nos saliera, puede que el puerto esté desactivado. Para ello usamos el comando `ufw`.

Ya hemos acabado con Ubuntu. Ahora vamos con CentOS.

Instalamos el demonio de http:

```bash
sudo yum install httpd
sudo ifup enp0s8  # Si no tienes configurado que se levante la interfaz de red 
sudo systemctl status httpd
sudo systemctl start httpd
```

CentOS suele ser bastante restrictivo con el firewall, por lo que, si intentas acceder a la página; al igual que Ubuntu, te dará fallo. Luego, al igual que en la práctica anterior, añadimos la regla al firewall:

```bash
sudo firewall-cmd --permanent --add-service=http
sudo firewall-cmd --reload
```

*Como curiosidad, el puerto 80 solo es para la escucha de peticiones, ya que si pidieses varias páginas web a la vez se saturaría. Por lo que al pedir la página web al puerto 80, le asignas el puerto por el que quiere que llegue la información.*

Ahora vamos a instalar la base de datos, para hacer que el servidor Apache se conecte a la base de datos:

```bash
sudo yum install mariadb
sudo yum install mariadb-server
```

Como siempres miramos que esté instalado y lo activamos:

```bash
sudo systemctl status mariadb
sudo systemctl start mariadb
```

*Por defecto, mariadb siempre se conecta al puerto 33 (podemos hacer que el servidor Apache se conecte a este puerto y pueda usar la base de datos). Cualquier persona con mi IP y sabiendo el puerto por defecto del mariadb puede conectarse como usuario root a la base de datos*

Como consecuencia de esto, vamos a ponerle usuario y contraseña.

```bash
mysql_secure_installation
```

Dice que nos conectemos como root, pero el root de mariadb, el cual, no tiene contraseña por defecto; luego, damos enter. A partir de ahí le damos todo `yes`.

Ahora vamos a instalar php:

```bash
sudo yum install php
php -a  # Para comprobar que está instalado (Igual que Ubuntu)
sudo yum install php-mysqli
```

Ahora que tenemos todo instalado, vamos a crear una página web con php en la carpeta `/var/www/html/`.

```bash
sudo nano /var/www/html/index.php
```

```php
<?php
    echo("Holi");
    $link = mysqli_connect('127.0.0.1:3306','root','practicas,ise');

    if(!$link)
        die("No se puede conectar a la BD");

    echo("Conectado a la BD");
    mysqli_close($link);
?>
```

*La IP a la que nos estamos conectando es la del localhost, después viene el puerto, el usuario y la contraseña.*

Vamos a ver que funciona:

```bash
# De forma local
sudo php /var/www/html/index.php
# En el navegador
192.168.56.110/index.php
# click derecho y darle a ver código fuente de la página
```

En el segundo caso, se baja el php entero, luego, hay que configurarlo para que se interprete como una página web:

```bash
sudo nano /etc/httpd/conf/httpd.conf
```

Buscamos `directoryindex` y añadimos `index.html, index.php`.

```bash
sudo systemctl restart httpd
```

Al recargar la página, lo interpretará como página web.

Ahora vamos a ver algunas de las variables de seguridad de CentOS. Si hemos seguido los pasos, vemos que al intentar acceder desde un navegador externo, no nos podemos conectar a la base de datos. Para ello:

```bash
# Para ver las variables de seguridad del sistema
sudo getsebool -a
sudo getsebool -a | grep httpd
# La activamos
sudo setsebool -P httpd_can_network_connect_db on
# Vemos que esté activada
sudo getsebool -a | grep httpd
```

Ahora, al recargar la página, veremos que si se conecta a la base de datos.

Con esto, ya hemos acabado esta parte de la práctica. Ahora, para finalizar, vamos a instalar un programa para aumentar la seguridad. Este programa se llama `fail2ban`, el cual, te echa del servidor en caso de fallar 5 veces al meter la contraseña.

Para ello, vamos a poner que se pueda conectar a ssh con contraseña (recordemos que lo desactivamos el día anterior).

```bash
sudo nano /etc/ssh/sshd_config
# Ponemos PasswordAuthentication a yes y reiniciamos
sudo systemctl restart sshd
```

Ahora vamos a instalar todo lo necesario para ejecutar `fail2ban`:

```bash
sudo yum install epel-release
sudo yum install fail2ban
sudo systemctl status fail2ban
sudo systemctl start fail2ban
sudo fail2ban-client
sudo fail2ban-client status
```

Vamos a crear cárceles para meter ahí a aquellas personas que fallan al conectarse. Para ello, modificamos el siguiente fichero:

```bash
sudo nano /etc/fail2ban/jail.conf
# Nos dice que no tenemos permiso, por lo que vamos a realizar el siguiente truco
cd /etc/fail2ban
ls
sudo cp -a jail.conf jail.local
# Al crear una copia local con el contecto podemos editarlo
sudo nano jail.local
```

En el fichero, buscamos la parte de ssh. Buscamos `# JAILS` con `CRTL+W` hasta llegar a la parte de ssh. En esta parte, añadimos `enabled = true` y cambiamos el puerto, ya que viene el por defecto.

![Captura de pantalla de 2022-04-07 21-06-43.png](.sources/Captura%20de%20pantalla%20de%202022-04-07%2021-06-43.png)



En este fichero también podemos configurar cosas de http o el tiempo máximo de baneo.

```bash
sudo systemctl restart fail2ban
sudo fail2ban-client status
```

Ahora, nos conectamos desde nuestro Linux a CentOS e introducimos de forma errónea la contraseña varias veces:

```bash
ssh danielav@192.168.56.110 -p 22022
```

Ahora si miramos el estado de nuevo, veremos que nuestr IP de Ubuntu aparece baneda. Podemos desbloquearla de la siguiente forma:

```bash
sudo fail2ban-client status
sudo fail2ban-client status sshd
sudo fail2ban-client set sshd unbanip 192.168.56.1
sudo fail2ban-client status sshd
```
