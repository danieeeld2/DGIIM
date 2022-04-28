# ISE Práctica 2

## Lección 1

###### Daniel Alconchel Vázquez

---

En la práctica de hoy configuraremos **ssh** tanto para CentOS como para Ubuntu. Vamos a comenzar por Ubuntu, ya que, como no tiene tantas restricciones de seguridad, será más simple.

Antes que nada, recuerda que necesitas las máquinas con la conexión red configurada.

Vamos a intentar **conectarnos a CentOS desde Ubuntu**, para ello, tenemos que seguir los siguientes pasos:

Primero **instalaremos en Ubuntu el servicio de servidor ssh** (El de cliente ya viene instalado por defecto en ambos sistemas), para ello:

```bash
sudo apt install openssh-server
# Iniciamos el servicio
sudo systemctl start sshd
sudo systemctl status sshd
```

Para comprobar el servicio vamos a probar a **conectarnos a Ubuntu desde CentOS**:

```bash
# ssh usuario@ip-Ubuntu
ssh danielav@192.168.56.105
```

**Importante:** Ahora todo lo que hagas en tu máquina CentOS se estará haciendo en Ubuntu. Para cerrar la conexión bata con ejecutar el comando `exit`.

Por defecto, **ssh utiliza el puerto 22**. Esto es bastante inseguro (*se puede aprovechar para hacer ataques de diccionarios*), por lo que, para mayor seguridad, vamos a cambiar el puerto al **22022**:

```bash
sudo nano /etc/ssh/sshd_config
# Descomentamos la línea Port 22 y la cambiamos por 22022
```

Puede ser también interesante impedir que nadie se pueda conectar por ssh como super usuario. Para ello, también el fichero anterior, descomentamos la línea `PermitRootLogin yes` y lo cambiamos a no.

Para que estas modificaciones funcionen tenemos que **reiniciar el servicio**, para lo que basta ejecutar el comando `sudo systemctl restart sshd`.

Al cambiar el puerto de conexión de ssh, tendremos que usar el siguiente comando para conectarnos:

```bash
# ssh usuario@ip-Ubuntu -p Port
ssh danielav@192.168.56.105 -p 22022
```

**Vamos ahora con CentOS**. En CentOS tanto el servicio de ssh cliente como el servidor vienen instalados por defecto, por lo que podemos pasar directamente a la parte de configuración.

Comenzamos **cambiando el puerto de conexión y el permiso de conexión como root**. Para ello, al igual que en Ubuntu:

```bash
sudo nano /etc/ssh/sshd_config
# Descomentamos la línea Port 22 y la cambiamos por 22022
# Descomentamos la línea PermitRootLogin yes y lo cambiamos a no
```

Si ahora intentamos reiniciar el servicio (`systemctl restart sshd`) nos dará un fallo, porque el sistema no espera que el puerto 22022 sea para ssh, por lo que tenemos que indicarle que queremos usar ese puerto para ssh. PAra ello vamos a seguir los siguientes pasos.

**Comenzamos actualizando los repositorios** (en caso de que no lo tuvieramos ya hecho):

```bash
cd /etc/yum.repos.d/
sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-*
sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g'
/etc/yum.repos.d/CentOS-*
```

**Vamos a instalar el paquete semanage**. Para ello, recuerda levantar previamente la interfaz de red con `ifup enp0s8` (Puede que también tengas que activar *enp0s3*).

El paquete no se puede instalar directamente. Si realizamos `sudo yum provides semanage` obtendremos las distintas dependencias requeridas. Instalamos la siguiente:

```bash
sudo yum install policycoreutils-python-utils
```

Ahora, ya podemos hacer uso del paquete. Si realizamos el comando `sudo semanage port -l | grep ssh` podremos ver que puertos están configurados para ssh. Notemos que el puerto *22022* no aparece en esa lista, por lo que vamos a añadirlo. Para ello:

```bash
sudo semanage port -a -t ssh_port_t -p tcp 22022
# Volvemos a comprobar que se ha añadido correctamente
sudo semanage port -l | grep ssh
```

Aunque hayamos especificado que el puerto *22022* está destinado a ssh, nos seguirá dando error. Esto se debe al **cortafuegos**, por lo que vamos a especificarle al mismo que vamos a hacer uso del puerto. Para ello:

```bash
sudo firewall-cmd --permanent --add-port=22022/tcp
# Recargamos el firewall
sudo firewall-cmd --reload
```

Ahora sí, ya podemos reinicar el servicio de shh (`sudo systemctl restart sshd`) y probar a **conectarnos de Ubuntu a CentOS**:

```bash
# ssh usuario@ip-CentOS -p Port
ssh danielav@192.168.56.110 -p 22022
```

Notemos que cada vez que nos conectamos tenemos que introducir la contraseña para autenticicarnos, por lo que vamos a configurar esto para que cuando nos conectemos no nos pida la misma.

**SIN SER ROOT y desde Ubuntu**, ejecutamos el comando `ssh-keygen` y le damos a enter en todos los pasos, para que la genere por defecto (*La configuración por defecto es guardar la clave en el archivo ~/.ssh/id_rsa.pub y no establecer contraseña a la clave*).

Para comprobar si esta nuestra clave podemos hacer `cat .ssh/id_rsa.pub`.

Ahora, **nos conectamos desde Ubuntu a CentOS, pero cambiando un poco el comando habitual:**

```bash
# ssh-copy-id usuario@ip-CentOS -p Port
ssh-copy-id danielav@192.168.56.110 -p 22022
```

Con esto, ya nos podemos conectar de Ubuntu a CentOS sin que nos pida contraseña. 

Una vez hecho esto, **una opción de seguridad interesante puede ser deshabilitar la posibilidad de conectarse a CentOS con contraseña**. Para hacerlo sería (desde CentOS):

```bash
sudo nano /etc/ssh/sshd_config
# Descomentar línea PasswordAuthentication yes y ponerlo a no
# Reiniciamos el servicio
sudo systemctl restart sshd
```
