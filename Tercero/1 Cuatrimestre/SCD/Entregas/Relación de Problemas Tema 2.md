# **Relación de Problemas Tema 2**

###### Daniel Alconchel Vázquez

------

## <u>Ejercicio 61</u>

```c++
#include <iostream>
#include "scd.h"

using namespace std;
using namespace scd;

// Variables Globales
const int 
    num_sillas_A = 4,
    num_sillas_B = 4;

class Monitor_Barberia : public HoareMonitor{
    private:
        int 
            sillas_A[num_sillas_A],
            num_libre_sillas_A,
            sillas_B[num_sillas_B],
            num_libre_sillas_B,
    		next_silla_A,
    		next_sila_B;
        CondVar
            entrada,
            salida,
            cola_espera_barbero[num_sillas_A],
            cola_pelandose[num_sillas_B];
    public:
        void 
            corte_de_pelo(int num_client),
            termina_corte_de_pelo(int num_client);
        int 
            siguiente_cliente();
        Monitor_Barberia();
};

Monitor_Barberia::Monitor_Barberia(){
    entrada = newCondVar();
    salida = newCondVar();
    for(int i=0; i<num_sillas_A; i++)
        cola_espera_barbero[i] = newCondVar();
    for(int i=0; i<num_sillas_B; i++)
        cola_pelandose[i] = newCondVar();
    num_libre_sillas_A = num_sillas_A;
    num_libre_sillas_B = num_sillas_B;
    for(int i=0; i<num_sillas_A; i++)
        sillas_A[i] = -1;
    for(int i=0; i<num_sillas_B; i++)
        sillas_B[i] = -1;
    next_silla_A = 0;
    next_silla_B = 0;
}

void Monitor_Barberia::corte_de_pelo(int num_client){
    int silla = 0;
    if(num_libre_sillas_B != 0){	// Si hay sillas libres para ser atendido
        sillas_B[next_silla_B] = num_client;	// El cliente ocupa la silla
        silla = next_silla_B;
        next_silla_B++;
        if(next_silla_B>=num_sillas_B)
            next_silla_B=0;
        num_libre_sillas_B--;
    }else{
        if(num_libre_sillas_A == 0)	// Si no hay sitio para esperar sentado
            entrada.wait();			// Bloqueamos la entrada, ya que nadie puede
        							// estar depie
        // En caso contrario el cliente entra, se sienta y espera
        sillas_A[next_silla_A] = num_client;
        silla = next_silla_A;
        next_silla_A++;
        if(next_silla_A>=num_sillas_A)
            next_silla_A=0;
        num_libre_sillas_A--;
        cola_espera_barbero[silla].wait();
        // Generamos tiempo aleatorio
        num_libre_sillas_A++;
        cola_espera_barbero[silla].signal();
        sillas_B[next_silla_B] = num_client;	
        silla = next_silla_B;
        next_silla_B++;
        if(next_silla_B>=num_sillas_B)
            next_silla_B=0;
        num_libre_sillas_B--;
    }
    
    cola_pelandose[silla].wait(); // El cliente esta pelándose, luego ese puesto se bloquea
    // Generamos tiempo aleatorio
    num_libre_sillas_B++;
    cola_pelandose[silla].signal();	// Liberamos el puesto
    salida.wait();	    // No dejamos salir al cliente hasta que pague
    entrar.signal();	// Permitimos la entrada de un nuevo cliente
}

void Monitor_Barberia::termina_corte_de_pelo(int num_client){
    // Desbloqueamos la salida para que el cliente salga y pague
    salida.signal();
}

int Monitor_Barberia::siguiente_cliente(){
    // Devuelve el último cliente sentado en una silla B (Silla de Barbero)
    if(next_silla_B != 0)
        return sillas_B[next_silla_B-1];
    return sillas_B[num_sillas_B-1];
}
```

## **<u>Ejercicio 62</u>**

```c++
#include <iostream>
#include "scd.h"

using namespace std;
using namespace scd;

const int num_plazas=100;
const int num_empleados=100;

class Garaje : public HoareMonitor{
    private:
    	CondVar 
            espera,
    		cobra[num_plazas],
    		lavado[num_plazas];
    	int
            libres,
    		siguiente_libre,
    		empleados[num_empleados];
    public:
    	Garaje();
    	void lavado_de_coche(int num_coche);
    	int siguiente_coche();
    	void terminar_y_cobrar(int num_coche);
};

Garaje::Garaje(){
    espera = newCondVar();
    for(int i=0; i<num_plazas; i++){
        cobra[i] = newCondVar();
        lavado[i] = newCondVar();
    }
    for(int i=0; i<num_empleados; i++)
        coches[i] = -1;
    siguiente_libre = 0;
    libres = num_plazas;        
}

void Garaje::lavado_de_coche(int num_coche){
    // Si no hay huecos libres, entonces espera
    if(libres == 0)
        espera.wait();
    // En caso contrario, procede a ocupar un hueco
    int posicion = siguiente_libre;
    // Asignamos un coche a un empleado
    empleados[posicion] = num_coche;
    siguiente_libre++;
    if(siguiente_libre >= num_plazas)
        siguiente_libre=0;
    libres--;
    // Bloqueamos ese puesto ya que hay un coche siendo lavado
    lavado[posicion].wait();
    cobrar[posicion].wait();
    // Aquí generaríamos un tiempo aleatorio que simule el tiempo de lavado
    // con chrono
    empleados[posicion]=-1;
    libres++;
    // Liberamos el puesto ya que el lavado del coche ha finalizado
    lavado[posicion]signal();
}

void Garaje::terminar_y_cobrar(int num_coche){
    for(int i=0; i<num_empleados; i++)
        if(empleados[i] == num_coche)
            // Cobramos al coche y liberamos al empleado
            cobrar[i].signal()
}

int Garaje::siguiente_coche(){
    for(int i=0; i<num_plazas;i++)
        if(empleados[i]!=-1)
            return i;
    return 0;
}

```

## <u>**Ejercicio 63**</u>

Nos piden comprobar que el monitor es correcto usando las reglas de correción de la operación c.wait() y c.signal() para señales desplazantes, considerando el IM:I=={0 $$\leq$$ n $$\leq$$ MAX}.

*Recordemos algunos conceptos:*

- *El Invariante del Monitor (IM) es una propiedad que el monitor cumple siempre y que es específica de cada monitor*

- *Axioma inicializacion de variables: El invariante del monitor debe ser cierto en su estado inicial, justo después de la inicialización de la variables permanentes.*

- *El invariante del monitor debe ser cierto antes y después de cada llamada a un procedimiento del monitor*

- *Axioma operacion c.wait():*
  $$
  \{IM\land L\}c.wait()\{C\land L\}
  $$

  - *El proceso que ocasiona la ejecución de c.wait se bloquea y deja lible el monitor*
  - *Entra en la cola FIFO aociada a c*
  - *Las demostraciones de corrección no tienen en cuenta laobligación de que el proceso termine de ejecutar c.wait()*

- *Axioma operacion c.signal():*
  $$
  \{\lnot vacio(c)\land L\land C\}c.signal()\{IM\land L\}
  $$

  - *No tiene efecto si la cola c está vacía*
  - *Se supone semántica desplazante: El monitor mantiene el estado expresado por C hasta que un proceso, que se bloqueó en la ejecución de c.wait(), se reanude y continúe con su ejecución dentro del monitor*
  - *Los axiomas no tienen en cuenta el orden de desbloqueo de los procesos*

Repasado dichos conceptos, volvamos al ejercicio (marcaré entre llaves el proceso de verificación):

```c++
Monitor Bufer;
var n, frente, atras: integer;
no_vacio, no_lleno: condition;
buf: array[1..MAX] of tipo_dato;
```

```c++
procedure insertar(d: tipo_dato);
	begin
    	{IM}
		if (atras mod MAX +1 == frente)	then
        {atras mod MAX+1 == frente ^ IM}
			no_lleno.wait()
            {atras mod MAX+1 != frente}
        else
        	{atras mod MAX*1 != frente}
            NULL;
        buf[atras]= d;
        atras = atras mod MAX + 1;
        n++;
		{frente!=atras}
        no_vacio.signal();
		{0<= n <= MAX ---> IM}
	end;
```

- **Linea 3**: IM debe ser cierto antes y después de un procedimiento del monitor
- **Línea 5:** El invariante del monitor debe ser cierto antes de la operación wait
- **Linea 7 y 9:** Axioma operación c.wait
- **Línea 14 y  16:** Axioma c.signal(), además de que IM debe ser cierto después de una operacion signal y que justo antes de una operación signal sobre una variable condición c, debe ser cierta la condición lógica C asociada a dicha variable

```c++
procedure retirar(var x:
		tipo_dato);
	begin
    {IM}
		if ( frente==atras) then
        	{frente==atras ^ IM}
            no_vacio.wait();
			{frente!=atras}
        else 
        	{frente!=atras}
            NULL;
        x= buf[frente];
        frente= frente mod MAX 1;
        n--;
		{atras mod MAX+1 != frente}
        no_lleno.signal();
		{0<= n <= MAX ---> IM}
    end;
```

- **Línea 4:** IM debe ser cierto antes y después de un procedimiento del monitor
- **Línea 6:** El invariante del monitor debe ser cierto antes de la operación wait
- **Línea 8 y 10:** Axioma operación c.wait
- **Línea 15 y 17:**  Axioma c.signal(), además de que IM debe ser cierto después de una operacion signal y que justo antes de una operación signal sobre una variable condición c, debe ser cierta la condición lógica C asociada a dicha variable

```c++
begin
    frente=1;
    atras= 1;
    n= 0;
	{IM}
end;
```

Con esto finaliza la verificación del monitor.

## <u>**Ejercicio 65**</u>

En este ejercicio disponemos del siguiente código:

```c++
Monitor M(){
    cond p,q;
    procedure stop{
        begin
            p.wait();
        	...
            q.singal();
        end;
    }
    procedure sigue{
        begin
            ...
            p.signal();
        	q.wait();
        end;
    }
    begin
    end;
}
```

El ejercicio nos dice que hay dos procesos, P1 y P2:

```c++
Proceso P1;
begin
	while TRUE do
		...
		M.stop();
		...;
end;
```

```c++
Proceso P2;
begin
	while TRUE do
	...
	M.sigue();
	...
end;
```

La intención original era que el proceso P1 esperase bloqueado en la cola de la señal p, hasta que el proceso P2 llamase al procedimiento M.sigue() para desbloquear el proceso P1; después P2 esperaría hasta que P! terminase de ejecutar M.stop(), tras realizar algún procesamiento se ejecutaría q.signal() para desbloquear a P2. Sin embargo, el programa se bloquea.

#### **Apartado A:**

El enunciado no nos dá ninguna suposición acerca de la velocidad de ejecución de los procesos ni cuál de ellos adquiere el monitor en primer lugar.

Supongamos que el proceso P2 es el primero en adquirir el monitor. En dicho caso, ejecutaría la sentencia **p.signal()** (que corresponde con la línea 13 de nuestro código). Esta sentencia no supondría ningún efecto, debido a que no hay ningún proceso esperando en la cola del monitor, ya que P1 no ha ejecutado el código del monitor, todavía. Acto seguido, ejecutaría  la sentencia **q.wait()**, lo que provocaría que P2 se quede esperando en la cola condición q, dejase el monitor y este fuera adquirido por P1. Una vez P1 adquiere el monitor, este ejecutará la sentencia **p.wait()** (línea 5), por lo que quedará bloqueado y esperando en la cola condición p. Como ambos procesos están bloqueados y a la espera de una señal que los reanude por parte del otro (la cual, evidentemente, nunca va a llegar, ya que ambos se encuentran bloqueados), tenemos una situación de interbloqueo.

Por otro lado, si suponemos que se ejecuta primero el proceso P1, entonces este ejecutaría **p.wait()** (línea 5), por lo que quedará bloqueado y esperando en la cola condición p, dando paso a que el proceso P2 adquiera el monitor. Este ejecutaría la sentencia **p.signal()**, liberando a P1. Es aquí donde encontramos el problema. Si P1 llegase a ejecutar **q.signal()** (línea 7) antes de que P2 ejecutase **q.wait()** (línea 14), entraríamos en otra situación de interbloqueo, ya que P2 pasaría a bloquearse y esperar en la cola condición q, mientras que P1 repetiría su código, ejecutándo la sentencia p.wait(), lo que le llevaría a bloquearse y quedar esperando en la cola condición p (Tenemos una condición de carrera). Luego, nuevamente, nos encintramos en el caso anterior.

#### **Apartado B:**

Para solucionar esta situación de interbloqueo, podemos considerar los siguientes cambios en el código:

```c++
procedure stop{
	begin
        /** 
        	Como este código es "cíclico", podemos hacer que desbloquee a q tanto al
        	principio como al final. De esta forma evitamos la condición de carrera
        	en este sector de código
        **/
        q.signal();
		p.wait();
		...
		q.singal();
	end;
}
procedure sigue{
    begin
        /**
        	Hacemos que el P2 espere a que P1 este bloqueado para proseguir su ejecución
        **/
        while(p.empty()){}
    	...
    	p.signal();
    	q.wait();
    end;
}
```

## <u>**Ejercicio 66**</u>

*Recordemos algunos conceptos:*

- *Monitores SC (Señalar y Continuar): Señal explícita, no desplazante. Usando este mecanismo de señalación, el señalador continúa inmediantamente la ejecución del código del monitor tras la llamada a signal, mientras que el señalado abandona la cola condición y espera en la cola del monitor hasta readquirir la E.M. tras la operación wait*
- *Monitores SU (Señales Urgentes): Señal explícita, desplazante, el proceso señalador espera en la cola de procesos urgentes. Con este mecanismo, el señalador se bloquea en la cola de urgentes hasta readquirir E.M. y ejecutar código del monitor tras signal (Para readquirir E.M. tiene más prioridad que los procesos en la cola del monitor), mientras que el señalado reanuda inmediantamente la ejecución de código del monitor tras la operación wait*
- *Monitores SE o SW (Señalar y Esperar/Wait): Señal explícita, desplazante, el proceso señalador espera en la cola de entrada al monitor. En esta ocasión, el señalador abandona el monitor (ejecuta código tras la llamada al procedimiento del monitor). Si hay código en este proceso, tras ejecutar signal, no se ejecuta inmediatamente. Por otro lado, el señalado reanuda inmediatamente la ejecución del código del procedimiento del monitor tras la operación wait*

Volvamos pues al ejercicio:

#### **Monitor1:**

```c++
Monitor Semaforo{
    int s;
    cond c;
    void* P(void* arg){
        if(s==0)
            c.wait();
        s=s-1;
    }
    void* V(void* arg){
        s=s+1;
        c.signal();
    }
    begin
        s=0;
    end;
}
```

Fijémonos en la **línea 6** de nuestro código. En este caso, necesitamos que la señal sea desplazante. Esto es debido a que un proceso señalado abandona la cola condición del monitor en dicha línea. Usando un  mecanismo de señales no desplazante, como es SC, el proceso esperará en la cola del monitor, a la espera de readquirir la E.M., pero cabe la posibilidad de que otros procesos hagan falsa la condición previa de la **línea 5** trás el abandono del proceso señalado de la cola condición, por lo que no se puede garantizar que **s==0** sea una condición cierta trás la ejecución de la **línea 6**, por lo que necesitaríamos volver a comprobar la condición. Para ello podemos realizar el siguiente cambio:

```c++
void* P(void* arg){
    while(s==0)
        c.wait();
    s=s-1;
}
```

De esta forma, el monitor sería válido para la semántica **SC** (semántica no desplazante).

Por otro lado,  el monitor original es válido para las semánticas **SU** y **SW**, ya que usan señales desplazantes, es decir, el monitor mantiene la condición **s==0** del proceso señalado (que está bloqueado por la ejecución de c.wait()) hasta que este se reanude y siga con la ejecución del monitor.

#### **Monitor2:**

```c++
Monitor Semaforo{
	int s;
    cond c;
    void* P(void* arg){
        while(s==0)
            c.wait();
        s=s-1;
    }
    void* V(void* arg){
        notifyAll();
        s=s+1;
    }
    begin
        s=0;
    end;
}
```

Para este caso, debemos prestar atención a las **líneas 10-11**. Por un lado, en la **línea 11** tenemos un **notifyAll()**, el cual, desbloquea todos los procesos bloqueados en la cola del monitor (cola c), aunque solo reanudará su ejecución uno de ellos, mientras que los otros esperan a que el monitor quede, nuevamente, libre.

Por otro lado, en la **línea 11** tenemos un aumento de la variable s. Si la semántica es no desplazante, es decir, usamos una semántica **SC** no hay problema alguno, ya que se ejecutará la línea 10 y, acto seguido, la 11; pero en el caso de semánticas desplazantes (**SU y SW**) puede ocurrir una situación de interbloqueo, como consecuencia de que la **línea 11** no se ejecute inmediatamente, ya que, en semánticas con desplazamiento, la hebra señaladora al salir del cerrojo da paso a la señalada,la cual, reanuda su ejecución (esto puede ocurrir antes de que se ejecute la **línea 11** lo que llevaría a ese interbloqueo).

Para solucionarlo, basta con intercambiar de posición el código de la línea 10 y 11:

```c++
void* V(void* arg){
	s=s+1;
    notifyAll();
}
```

#### **Monitor3:**

```c++
Monitor Semaforo{
	int s;
	cond c;
	void* P(void* arg){
		if(s==0)
			c.wait();
		else
			s=s-1;
	}
	void* V(void* arg){
        if(c.queue())
            c.signal();
        else
            s=s+1;
    }
    begin
        s=0;
    end;
}
```

Aparentemente, funciona en los 3 casos.

## <u>**Ejercicio 68**</u>

Nos piden que consideremos un número desconocido de procesos productores y consumidores de mensajes de una red de comunicaciones. Los mensajes de los productores se enviarán mediante el método **broadcast(int m)** y envia una copia del mensaje a las hebras consumidoras, que previamente lo hayan solicitado (estas se encuentran bloqueadas, esperando). Además, otra hebra productora no puede enviar el siguiente mensaje hasta que todas las hebras consumidoras reciban el último mensaje enviado.

Por otro lado, las hebras consumidoras llaman a la operación **int fetch()** para recibir una copia del mensaje enviado. Mientras un mensaje esté transmitiéndose por la red, las nuevas hebras consumidoras que soliciten recibirlo, lo recibirán inmediatamente, sin espera. Mientras este proceso ocurre, la hebra consumidora que envió el mensaje permanece bloqueada.

Nos pides una solución usando monitores SU, luego una posible implementación sería:

```c++
class Monitor_RED{
    private:
    CondVar
        prod[a],
    	cons[b];
    	// Como es un número desconocido pondremos a y b (podría hacerse usando
    	// la clase vector de la stl)
    int 
        mensaje,
    	esperando;
    public:
    	void broadcast(int m);
    	int fetch(),
    	Monitor_RED();
};

Monitor_RED::Monitor_RED(){
    for(int i=0; i<a; i++)
        prod[i] = newCondVar();
    for(int i=0; i<b; i++)
        cons[i] = newCondVar();
    mensaje=0;
    esperando=;
}

void Monitor_RED::broadcast(int m){
    // Si hay un proceso transmitiendo, bloqueamos el resto, ya que estos no pueden
    // transmitir
    if(transmitiendo)
        for(int i=0; i<a; i++)
            if(i!=num_proceso_transmitiendo)
                prod[i].wait();
    // Si no hay ninguno, el primero que llegue transmite
    transmitiendo = true;
    mensaje = m;
    while(esperando)
        for(int i=0; i<b; i++)
            if(/*Usando vectores de la stl podemos crear un vector auxiliar
            	que almacene los consumidores que han solicitado el mensaje y si
            	i pertenece a esa lista, entonces les manda una señal*/)
                cons[i].signal();
    transmitiendo=false;
    if(esperando==0)
        for(int i=0; i<a; i++)
            prod[i].signal();
}

int Monitor_RED::fetch(){
    // Si el proceso lo solicita, lo almacenamos en ese vector que hemos comentado
    // con anterioridad
    esperando++;
    for(int i=0; i<b; i++)
        cons[i].wait();
    // Los bloqueamos y si son liberados recibirandicho mensaje
    esperando--
    return mensaje;    
}
```

