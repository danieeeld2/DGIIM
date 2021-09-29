# RESUMEN TEORÍA

###### DANIEL ALCONCHEL VÁZQUEZ

------

## TEMA 1: INTRODUCCIÓN A LA COMPUTACIÓN

Un **alfabeto** es un conjunto finito *A*. Sus elementos se llamarán **símbolos o letras**.

```
Notación:
	- Alfabetos: A,B,C...
	- Símbolos: a,b,c...
```

Una **palabra** sobre el alfabeto *A* es una sucesión finita de elementos de *A*.
$$
u=a_1...a_n,\quad a_i\in A, \forall i=1,...,n
$$

```
Ejemplo:
Si tenemos A={0,1}, entonces 0011 es una palabra del alfabeto
```

El **conjunto de todas las palabras** sobre un alfabeto *A* se nota como *A* *.

```latex
Notación:
	- Palabras: u,v,x,y...
	- Longitud de la palabra (número de símbolos que la forman): si u=a_1...a_n --> |u|=n
	- Palabra vacía: \epsilon (tiene longitud cero)
	- El conjunto de cadenas sobre un alfabeto A, excluyendo la cadena vacía: A^+
```

Llamamos **concatenación** a:
$$
u,v\in A^*,u=a_1...a_n;\;v=b_1...b_m\overset{concatenacion}{\implies}uv=u.v=a_1...a_nb_1...b_m
$$

```
Ejemplo:
Si u=011 y v=1010, entonces tenemos que uv=0111010
```

La concatenación verifica las siguientes propiedades:
$$
1)|u.v|=|u|+|v|\qquad\forall u,v\in A^*\\
2)Asociativa: u.(v.w)=(u.v).w, \qquad \forall u,v,w\in A^*\\
3)Elemento\; neutro:u.\epsilon=\epsilon.u=u, \qquad \forall u\in A^*
$$
Definimos **prefijo** y **sufijo** con la connotación del lenguaje natrual. Matemáticamente sería:
$$
Prefijo:Si\;u\in A^*,v\;es\;prefijo\;si\;\exists z\in A^*:vz=u\\
Sufijo:Si\;u\in A^*,v\;es\;un\;sufijo\;si\;\exists z\in A^*: zv=u
$$
Se dicen **propios** si no son ni el vacio ni el total.

Definimos **iteración n-ésima** de una cadena ($$u^n$$) como la concatenación con ella misma n veces. Cumple las siguientes propiedades:
$$
1)u^0=\epsilon\\
2)u^{i+1}=u^i.u,\qquad \forall i\geq 0
$$

```
Ejemplo:
Si u=010, entonces u^3=010010010
```

Definimos **cadena inversa** como invertir de orden los símbolos que componen la cadena. Matemáticamente:
$$
u=a_1...a_n\in A^*\overset{c.inversa}{\implies}u^{-1}=a_n...a_1\in A^*
$$

```
Ejemplo:
Si u=011, entonces u^-1=110
```

Un **lenguaje** sobre el alfabeto *A* es un subconjunto del conjunto de las cadenas sobre *A*: $$A: L\subseteq A^*$$.

Un conjunto se dice **numerable** si existe una aplicación inyectiva de este conjunto en el conjunto de los números naturales, o lo que es lo mismo, se le puede asignar un número natural a cada elemento del conjunto de tal manera que dos elementos distintos tengan números distintos.