### Ejercicios Tema 2

###### Daniel Alconchel Vázquez

###### Mario García Márquez

###### Jesús García León

------

**9.- Cuestiones sobre procesos, y asignación de CPU:**

**a) ¿Es  necesario  que  lo  último  que  haga  todo  proceso  antes  de  finalizar  sea  una  llamada  al  sistema  para finalizar? ¿Sigue siendo esto cierto en sistemas monoprogramados?**

Si, es necesario decirle al sistema de que tiene que finalizar dicho proceso y quitarlo de la memoria para poder cargar otro (Modelo de los 5 estados). En un sistema monoprogramado se  mantiene esta idea, ya que en dichos sistemas se ejecuta un proceso y, hasta que este no finaliza, no comienza otro.

**b) Cuando el controlador de un dispositivo produce una interrupción ¿se produce necesariamente un cambio de contexto?, ¿y cuando se produce una llamada al sistema?** **¿Sigue siendo ciertos en sistemas monoprogramados?**

Si, ya que es la manera que tiene el ordenador de detener el proceso. Esto sigue siendo verdad en sistemas monoprogramados, ya que permite detener un proceso para poder iniciar uno nuevo.

**c) Cuando un proceso se bloquea, ¿deberá encargarse él directamente de cambiar el valor de su estado en el descriptor de proceso o PCB?**

No, es el sistema operativo el que se encarga de cambiar el valor de su estado en el descritor de procesos.

**d) Sea  un  proceso  que  cambia  de  Ejecutándose  a  Bloqueado,  ¿puede  este  cambio  provocar  un  cambio  de estado en otros procesos? Si es así, ¿en qué casos?**

Sí, en multiprogramación mientras un proceso está bloqueado, los recursos de ese proceso pueden pasar a otro distinto.

**e) Idem para el cambio de estado Bloqueado a Ejecutable.**

No, ya que si este se ejecuta es porque se ha decidido que hay suficientes recursos para que este se ejecute.



**11.- ¿Por qué no es el intérprete de órdenes (shell) parte del propio sistema operativo? ¿Qué ventajas aporta el no serlo?**

Hay varias razones. La primera es que no todo los ordenadores necesitan  un shell ya que hay algunos que unicamente se decican a correr indefinidamente un único proceso. También es caso de que queramos que nuestro sistema operativo sea multiusuario, el shell no debe ser un proceso que pertenezca unicamente a uno de estos. Por último, cada uno puede usar distinto shell.



**16.- Suponga  que  la  tabla  de  páginas  para  el  proceso  actual  se  parece  a  la  de  la  figura.  Todoslos  números  son decimales,  la  numeración  comienza  en  todos  los  casos  desde  cero,  y  todas  las  direcciones  de  memoria  son direcciones en bytes. El tamaño de página es de 1024 bytes.**

| Número de página virtual | Número de marco de página |
| :----------------------: | :-----------------------: |
|            0             |             4             |
|            1             |             7             |
|            2             |             1             |
|            3             |             2             |
|            4             |            10             |
|            5             |             0             |

**¿Qué direcciones físicas corresponderán con cada una de las siguientes direcciones lógicas del proceso?**

**a) 999**

**b) 2121**

**c) 5400**
$$
Dirección\; física = Tamaño\; página\cdot Marco+Desplazamiento
$$
0) 5120

1) 8192

2 ) 2228

3) 3072

4) 11264

5) 1024



**18.- Suponga que un proceso emite una dirección lógica igual a  2453 y que se  utiliza la técnica de  paginación, con páginas de 1024 palabras**

**a) Indique el par de valores (número de página, desplazamiento) que corresponde a dicha dirección.**

**b) ¿Es posible que dicha dirección lógica se traduzca en la dirección física 9322? Razónelo**

Pendiente