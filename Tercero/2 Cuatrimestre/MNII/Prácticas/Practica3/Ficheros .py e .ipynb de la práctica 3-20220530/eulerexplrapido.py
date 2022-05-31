## módulo eulerexplrapido
''' método de Euler para resolver el PVI
    X,Y     = integrate(F,x0,y0,x1,h).
    {y}'    = {F(x,{y})}, donde
    {y}     = {y[0],y[1]}.
    x0,y0   = condiciones iniciales 
    x1      = valor final de la variable x0 + h en este caso
    h       = incremento de x usado para la integración
    F       = función suplida por el usuario
'''
import numpy as np
def integrate(F,x0,y0,h):    
    return y0 + h*F(x0,y0)
