# Reto 1. Eficiencia

###### Daniel Alconchel Vázquez

------

##### **<u>EJERCICIO 1</u>**

```c++
//Apartado a
void eficiencia1(int n){
    int x=0;	// O(1)
    int i,j,k;	// O(1)
    for(i=1; i<=n; i+=4)
        for(j=1; j<=n; j+=n/4)
            for(k=1; k<=n; k*=2)
                x++;	// O(1)
}
```

Para este primer algoritmo nos centramos en los bucles, ya que el resto (incluido las condiciones de dentro de los bucles) son O(1). Analizando los bucles encontramos:

- El primer bucle (línea 5) claramente tiene eficiencia O(n) cuando el número de datos tiende a infinito
- El segundo bucle (línea 6) solo se ejecuta unas 4 veces, por lo que su eficiencia es O(1)
- En tercer bucle (línea 7) vemos que, debido a la forma en la que aumenta el contador k (k*=2), el bucle realizará $log_2(n)$ cuando $n \to \infin$ , lo que equivale a O(log(n))

Como los bucles están anidados, usamos la regla del producto, donde obtenemos $O(n) \cdot O(1) \cdot O(log(n)) = O(nlog(n))$

Esta última eficiencia corresponde con la del algoritmo.



```c++
//Apartado b
int eficiencia2(bool existe){
    int suma2 = 0;	//O(1)
    int j,k,n;	//O(1)
    
    if(existe)	
        for(k=1; k<=n; k*=2)
            for(j=1; j<=k; j++)
                sum2++;	//O(1)
    else
        for(k=1; k<=n; k*=2)
            for(j=1; j<=n; j++)
                sum2++;	//O(1)
    return sum2;	//O(1)
}
```

Notemos que en este algoritmo encontramos dos bloques de código independientes, el bloque del if y el bloque del else, por lo que la eficiencia del algoritmo será la del bloque de mayor complejidad.

Para comenzar, todas las asignaciones y condiciones de los bucles for son O(1), por lo que para determinar que bloque tiene mayor complejidad nos centraremos, nuevamente, en los bucles. En este caso, el primer bucle de cada bloque es el mismo, por lo que nos fijamos en el segundo. Claramente, se puede observar que el segundo bucle del bloque else hace mayor número de iteraciones que el del bloque if, por lo que el bloque else será el de mayor complejidad. Centrándonos en el observamos:

- Primer bucle tiene una eficiencia de O(nlog(n)) (Mismo razonamiento que en el ejercicio anterior)
- Segundo bucle (línea 12) realiza n iteraciones, por lo que su eficiencia será O(n)

Nuevamente, aplicando la regla del producto, ya que los bucles están anidados, la eficiencia del bloque else, así como de la totalidad del algoritmo, será, nuevamente, O(nlog(n))



```c++
//Apartado c
void eficiencia3(int n){
    int j;	// O(1)
    int i = 1;	// O(1)
    int x = 0;	// O(1)
    do{
        j=1;	// O(1)
        while(j <= n){
            j=j*2;	// O(1)
            x++;	// O(1)
        }
        i++;	// O(1)
    }while(i<=n);
}
```

Al igual que en los casos anteriores, la complejidad del algoritmo se encuentra en el número de iteraciones que realizan los bucles.

- Notemos que el bucle while que se encuentra anidado es similar a los bucles for que hemos visto ateriormente, cuya eficiencia era $log_2 n$, por lo que su eficiencia será O(nlog(n))
- El bucle do while realiza n iteraciones, por lo que su eficiencia será O(n)

Nuevamente, usando la regla del producto, obtenemos que la eficiencia del algoritmo es O(nlog(n))



```c++
//Apartado d
void eficiencia4(int n){
    int j;		// O(1)
    int i=2;	// O(1)
    int x=0:	// O(1)
    do{
        j=1;	// O(1)
        while(j <= i){
            j=j*2;	// O(1)
            x++;	// O(1)
        }
        i++;	// O(1)
    }while(i<=n);
}
```

Nuevamente, la complejidad del algoritmo se encuentra en el número de iteraciones que realizan los bucles.

- Podemos observar que el bucle do while realiza n iteraciones, por lo que su eficiencia sera O(n)
- El bucle while es parecido al anterior, solo que en vez de realizar $log_2 n$ iteraciones, realiza $log_2 i$ iteraciones, pero como $i \to n$, entonces la eficiencia del  bucle while es O(log(n))

Nuevamente, usando la regla del producto, obtenemos que la eficiencia del algoritmo es O(nlog(n))



**<u>EJERCICIO 2</u>**

```c++
void eliminar(Lista L, int x){
    int aux, p;	//O(1)
    for(p=primero(L); p!=fin(L);){
        aux=elemento(p,L);
        if(aux==x)	// La condición es O(1)
            borrar (p,L);
        else
            p++;	//O(1)
    }
}
```

**<u>Apartado a</u>**

Para este apartado tenemos que primero es  O(1) y  fin,  elemento y  borrar son  O(n), por lo que :

- La condición del bucle for (línea 3), por la regla de la suma sería $O(O(n)+O(1)) = O(n)$ (Como las 3 funciones son independientes dentro del código, la eficiencia sigue siendo O(n))
- La eficiencia del código de dentro del bucle, por la regla de la suma, es O(n)

Esto hace que la eficiencia total del bucle, sin tener en cuenta el número de iteraciones, sea O(n)

- En el peor de los casos (no se cumple la condición del if), el bucle realizará n iteraciones, por lo que la eficiencia será de O(n)

Teniendo en cuenta que la eficiencia del bucle es O(n) y este se ejecuta n veces, por la regla del producto, la eficiencia resultante será de O(n²), que, además, corresponde con la del algoritmo, ya que el resto de código es independiente, por lo que usando la regla de la suma tendríamos $O(O(n²)+O(n)) = O(n²)$ 

Un posible cambio para mejorar el código es almacenar el valor de fin(L) en una variable, así evitamos llamar a la función en cada iteración pero esto no disminuye la complejidad del algoritmo, cuya eficiencia sigue siendo de O(n²).

```c++
void eliminar(Lista L, int x){
    int aux, p;	//O(1)
    int fin = fin(L); //O(n)
    for(p=primero(L); p!=fin;){	// O(1)
        aux=elemento(p,L);	//O(n)
        if(aux==x)	// La condición es O(1)
            borrar (p,L);	//O(n)
        else
            p++;	//O(1)
    }
}
```



**<u>Apartado b</u>**

Para este apartado tenemos que primero,  elemento y  borrar son  O(1) y  fin es  O(n), por lo que:

- La condición del bucle for (línea 3), por la regla de la suma sería $O(O(n)+O(1)) = O(n)$ 
- La eficiencia del código de dentro del bucle, por la regla de la suma, es O(1)

Esto hace que la eficiencia total del bucle, sin tener en cuenta el número de iteraciones, sea O(n)

- En el peor de los casos (no se cumple la condición del if), el bucle realizará n iteraciones, por lo que la eficiencia será de O(n)

Teniendo en cuenta que la eficiencia del bucle es O(n) y este se ejecuta n veces, por la regla del producto, la eficiencia resultante será de O(n²), que, además, corresponde con la del algoritmo, ya que el resto de código es independiente, por lo que usando la regla de la suma tendríamos $O(O(n²)+O(n)) = O(n²)$ 

Al igual que el apartado aterior, un posible cambio para mejorar el código es almacenar el valor de fin(L) en una variable, así evitamos llamar a la función en cada iteración pero, en esta ocasión, si permite mejorar la eficiencia del código, ya que la eficiencia de la condición del bucle pasaría a ser O(1), por lo que, por la regla del producto, la eficiencia del bucle pasaría a ser O(n), por lo que tendriamos $O(O(n)+O(n)) = O(n)$ 

```c++
void eliminar(Lista L, int x){
    int aux, p;	//O(1)
    int fin = fin(L);	//	O(n)
    for(p=primero(L); p!=fin;){	// O(1)
        aux=elemento(p,L); // O(1)
        if(aux==x)	// La condición es O(1)
            borrar (p,L);	// o(1)
        else
            p++;	//O(1)
    }
}
```



**<u>Apartado c</u>**

Para este apartado tenemos que todas las funciones son  O(1), por lo que:

- La condición del bucle for (línea 3) es O(1)
- La eficiencia del código de dentro del bucle, por la regla de la suma, es O(1)

Esto hace que la eficiencia total del bucle, sin tener en cuenta el número de iteraciones, sea O(1)

- En el peor de los casos (no se cumple la condición del if), el bucle realizará n iteraciones, por lo que la eficiencia será de O(n)

Teniendo en cuenta que la eficiencia del bucle es O(1) y este se ejecuta n veces, por la regla del producto, la eficiencia resultante será de O(n), que, además, corresponde con la del algoritmo, ya que el resto de código es independiente, por lo que usando la regla de la suma tendríamos $O(O(n)+O(1)) = O(n)$ 

En este caso, ya que todas las funciones son O(1), es imposible mejorar la eficiencia del código.

