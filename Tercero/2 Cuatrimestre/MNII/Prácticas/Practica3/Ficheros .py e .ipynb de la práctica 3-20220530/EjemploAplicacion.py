# -*- coding: utf-8 -*-
"""
Created on Mon May  4 19:12:05 2020

@author: prodelas
"""

import numpy as np
import sympy as sp

# Configuramos e importamos el submódulo Pyplot de Matplotlib
# %config InlineBackend.figure_format='retina'
import matplotlib.pyplot as plt


a = 0; b = 1;   # extremos inferior y superior del intervalo 
ya = 1          # condición inicial del PVI  y(a) = ya

def f(t,z):     # función de dos variables f(t,z) que define la 
    return z    # EDO de primer orden     y'(t) = f(t, y(t))

t = sp.Symbol('t')
sol_exacta = sp.E**t  # solución exacta, en caso de conocerse

# Esto permitiría la conversión de esta expresión en una función evaluable
y_x = sp.lambdify(t, sol_exacta, 'numpy')

n=10;  # con un valor concreto de n efectuaremos los cálculos

import euler

xx, yEuler = euler.integrate(f,a,ya,b,n)
# y asignémosle los arrays que devuelve a las abcisas y ordenadas
# que justo a continuación podremos dibujar y comparar con la sol. exacta
print("aprox. usando Euler", yEuler)

fig, ax = plt.subplots(figsize=(8, 4))
ax.plot(xx,yEuler, 'ro',label = "aprox. mét. Euler")
ax.plot(xx, y_x(xx), label="sol. exacta")
ax.set_title(r"Sol. exacta:  $y(t)=%s$" % sp.latex(sol_exacta), fontsize=18)
ax.set_xlabel(r"$t$", fontsize=18)
ax.set_ylabel(r"$y$", fontsize=18)
ax.legend()
fig.tight_layout()
plt.savefig("euler.pdf")
# fig.show()



import RK4

xx, yRK4 = RK4.integrate(f,a,ya,b,n)
# y asignémosle los arrays que devuelve a las abcisas y ordenadas
# que justo a continuación podremos dibujar y comparar con la sol. exacta
print("aprox. usando RK4", yRK4)

fig, ax = plt.subplots(figsize=(8, 4))
ax.plot(xx,yRK4, 'bo',label = "aprox. mét. RK4")
ax.plot(xx, y_x(xx), label="sol. exacta")
ax.set_title(r"Sol. exacta:  $y(t)=%s$" % sp.latex(sol_exacta), fontsize=18)
ax.set_xlabel(r"$t$", fontsize=18)
ax.set_ylabel(r"$y$", fontsize=18)
ax.legend()
fig.tight_layout()
plt.savefig("RK4.pdf")



# comparemos finalmente ambos métodos a la vez
# de manera gráfica
fig, ax = plt.subplots(figsize=(8, 4))
ax.plot(xx,yEuler, 'ro',label = "aprox. mét. Euler")
ax.plot(xx,yRK4, 'bo',label = "aprox. mét. RK4")
ax.plot(xx, y_x(xx), label="sol. exacta")
ax.set_title(r"Sol. exacta:  $y(t)=%s$" % sp.latex(sol_exacta), fontsize=18)
ax.set_xlabel(r"$t$", fontsize=18)
ax.set_ylabel(r"$y$", fontsize=18)
ax.legend()
fig.tight_layout()
plt.savefig("Comparativa.pdf")

