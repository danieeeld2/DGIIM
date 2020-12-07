# Práctica 3: TDA LINEALES

------

### TDA Pila_max:

Implementar una pila con máximo. Cada posición de la pila consta de dos valores. Uno es el dato nuevo introducido, y otro es el máximo valor de la pila. Recordar que:

- Las insercciones se hacen en el tope
- Los borrados se hacen en el tope
- Las consultas se hacen en el tope

#### Tareas a realizar:

- Especificaciones de la clase en el .h (comentadas con doxygen)
- Implementar dichas operaciones
- Programar test de prueba

#### Estructura a usar:

- Implementar usando una cola (**Pila_max_Cola**)
- Implementar usando un vector dinámico (**Pila_max_VD**)

Una vez realizada las dos estructuras anteriores, se pide crear un Pila_max.h con el siguiente código:

```c++
#define CUAL_COMPILA 2
#if CUAL_COMPILA==1
#include <pila_max_vd.h>
#elif CUAL_COMPILA==2
#include <pila_max_cola.h>
#endif
```



### Tarea Voluntaria:

Construir **TDA Cola_max**. La idea es igual que el apartado anterior,solo que ahora se trata de una cola.

#### Estructura a usar:

- Implementar usando **TDA Pila**