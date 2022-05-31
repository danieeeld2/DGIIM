## módulo rk

class Butcher:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    
    def __repr__(self):
        s = ''
        for i in range(len(self.a)):
            s += "{: >6} │ ".format(str(self.c[i])[:6])
            for j in range(len(self.a)):
                s += "{: >6} ".format(str(self.a[i][j])[:6])
            s += '\n'
        s += "───────┼─"
        for i in range(len(self.a)):
            s += "───────"
        s += "\n       │ "
        for i in range(len(self.a)):
            s += "{: >6} ".format(str(self.b[i])[:6])
        return s
    
    @classmethod
    def from_matrix(self,matrix):
        a = []
        b = []
        c = []
        for i in range(len(matrix)-1):
            c.append(matrix[i][0])
            b.append(matrix[len(matrix)-1][i+1])
            v = []
            for j in range(len(matrix)-1):
                v.append(matrix[i][j+1])
            a.append(v)
        return Butcher(a,b,c)

    def is_explicit(self):
        explicit = True
        for i in range(len(self.a)):
            for j in range(i+1, len(self.a)):
                if self.a[i][j] != 0:
                    explicit = False
        return explicit


''' método Runge-Kutta explícito para resolver el PVI a partir de un arreglo de Butcher
    X,Y     = integrate(F,x0,y0,xfinal,N).
    {y}'    = {F(x,{y})}, donde
    {y}     = {y[0],y[1],...y[N-1]}.
    x0,y0   = condiciones iniciales 
    xfinal  = valor final de la variable x
    h       = incremento de x usado para la integración
    F       = función suplida por el usuario que devuelve 
            el array F(x,y) = {y'[0],y'[1],...,y'[N-1]}.
    butcher = arreglo de Butcher para el método
'''
def integrate(F,x0,y0,xfinal,butcher,N):
    import numpy as np
    
    if ( butcher.is_explicit() ):
        def phi(F,x0,y0,h,butcher):
            tam = len(butcher.a)
            k0 = F(x0,y0)
            k = np.array([k0])
            
            for i in range(1, tam):
                kx = 0
                for j in range(i):
                    kx += k[j] * butcher.a[i][j]
                k = np.append(k, F(x0 + h*butcher.c[i], y0 + h*kx))
                
            return np.dot(butcher.b, k)

        
        X = np.linspace(x0,xfinal,N+1)
        Y = [y0]; h = (xfinal-x0)/N
        
        for n in range(N):
            Y.append( Y[n] + h*phi(F,X[n],Y[n],h, butcher) )
        
        return np.array(X),np.array(Y)
    else:
        print("Debe tratarse de un método explicito")
        return None
