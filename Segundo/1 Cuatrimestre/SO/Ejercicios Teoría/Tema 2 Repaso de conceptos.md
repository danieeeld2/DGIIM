## Tema 2: Repaso de conceptos

###### Daniel Alconchel Vázquez

------

**1.- Suponga un sistema multiprogramado con dos procesos. El proceso P1 esta preparado para ejecutarse y P2 esta atualmente en estado "EJECUTANDO". En un momento dado, P2 realiza una llamada para leer el contenido de un archivo (por ejemplo write()). Explicar los pasos que se sigue el sistema operativo tras la invocación de dicha llamada al sistema, haciendo especial hincapié en las trasinciones entre estados y los eventos que disparan dichas transiciones.**

Como sabemos, todo proceso del sistema operativo presenta un estado que  indica la situación de la ejecución en que se encuentra. 

Para empezar, el proceso P2 se encuentra ejecutandose. En este estado, el proceso está empleando CPU. Por otro lado, el proceso P1 está preparado para ejecutarse, es decir, es candidato a pasar activo.

Cuando el proceso P2 hace la llamada al sistema, pasa a estado bloqueado, ya que está pendiente de un evento externo que le ha hecho bloquear, que en este caso es esperar a que acabe la lectura del contenido del archivo.  Una vez acabado, se avisa al sistema mediante una interrupción, para que compruebe los procesos que estaban bloqueados y vuelvan al estado de preparado.

A continuación, el SO comprobará el planificador del sistema operativo, para ver que proceso tiene más prioridad, si P1 o P2. El que tenga mayor prioridad pasara a estado activo y cuando haya finalizado, realizará una llamada al sistema para su propia terminación, entrando en estado de terminado. El otro proceso que queda pasará, entonces, a estado activo y hará lo mismo que el anterior.

**2.-  Concepto de hilos (o hebra) y tipos. En un proceso multihebrado ¿qué comparte un hilo con sus 'hermanos'?**

Un hilo es una línea de ejecución de un proceso. Todo proceso parte inicialmente con un único hilo principal, aunque el  sistema operativo ofrece llamadas al sistema que permiten al programador crear y destruir hilos. Por tanto, un proceso está compuesto por uno o  más hilos.

Los hilos presentan estados, los principales de ellos son: Ejecución,  Listo y Bloqueado. No tiene sentido asociar estados de suspensión de  hilos ya que es un concepto de proceso. En todo caso, si un proceso está expulsado de la memoria principal (ram), todos sus hilos deberán  estarlo ya que todos comparten el espacio de direcciones del proceso.