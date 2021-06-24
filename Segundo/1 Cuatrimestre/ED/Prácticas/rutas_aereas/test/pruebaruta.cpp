/**
 * @author Mario Garcia Marquez y Daniel Alconchel Vazquez
 * @file pruebaruta.cpp
 */

#include "../include/Ruta.h"
#include <sstream>
#include <iostream>

using namespace std;

int main(){
    Ruta A;
    cout << "Probando clase Ruta: " << endl;
    cout << "Constructor: " << endl;
    cout << A << "=" << "0" << endl;
    cout << "Probando Sets/Gets:" << endl;
    A.nuevoNombre("Ruta1");
    cout << A.GetNombre() << "=Ruta1" << endl;
    Punto a(12,12);
    Punto b(0,0);
    A.nuevoPunto(b);
    A.nuevoPunto(a);
    A.nuevoInteres(a);
    cout << A << "= Ruta1 2 (0,0) (12,12)" << endl;
    cout << "Operator= y Constructor de copia" << endl;
    cout << "Operator= y Constructor de copia" << endl;
    Ruta B(A);
    Ruta C = A;
    cout << B << "=" << A << endl;
    cout << C << "=" << A << endl;
    cout << "Operator>>: " << endl;
    stringstream s("R4 	11 (14.422538164676899,-87.63432239999997) (48.85887766623369,2.3470598999999766) (24.725939314861463 ,46.822528799999986) (58.695433501291085,-96) (35.08690549340541,-103.72339606166992) (-12.055345316962327,-77.04518530000001)	(40.40051528912146,-3.5916460749999635) (37.943768420529985,104.13611175000005) (-27.787075486256633,133.28132295)	(35.673473752079516,139.71038800000008) (62.88647107195116,61.551173617626986)");
    Ruta D;
    s >> D;
    cout << D;

    return 0;
}