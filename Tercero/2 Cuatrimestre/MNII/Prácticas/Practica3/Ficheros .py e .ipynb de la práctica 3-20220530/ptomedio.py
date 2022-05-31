## módulo ptomedio
''' método del punto medio para resolver el PVI
    X,Y     = integrate(F,x0,y0,xfinal,n).
    {y}'    = {F(x,{y})}, donde
    {y}     = {y[0],y[1],...y[n-1]}.
    x0,y0   = condiciones iniciales 
    xfinal  = valor final de la variable x
    h       = incremento de x usado para la integración
    F       = función suplida por el usuario que devuelve 
            el array F(x,y) = {y'[0],y'[1],...,y'[n-1]}.
'''
import numpy as np
def integrate(F,x0,y0,xfinal,n):    
    X = np.linspace(x0,xfinal,n+1)
    Y = [y0]; h = (xfinal-x0)/n
    for i in range(n):
        Y.append(Y[i]+h*F(X[i]+h/2,Y[i]+h/2*F(X[i],Y[i])))
    return np.array(X),np.array(Y)
