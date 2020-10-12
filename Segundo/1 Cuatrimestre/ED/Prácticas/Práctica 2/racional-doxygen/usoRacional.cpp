#include <iostream>
#include <Racional.h>

using namespace std;

int main(void){

  Racional a,b,c,e,f,g,w,z;
  Racional d(2,4);

  a.print();
  cout << " Racional a\n";

  d.print();
  cout << " Racional d\n";

  a = d;
  a.print();
  cout << " Racional a tras asignarle el racional d\n";

  a.asignar(6,4);
  d.asignar(5,7);
  cout << d;
  cout << " Racional d 5/7 \n";
  a.print();
  cout << " Racional a 6/4 \n";
  c = a+d;
  c.print();
  cout << " Racional c=a+d\n";
  c.simplifica();
  cout << "Racional c=a+d irreducible " << c << endl;

  c += a;
  c.print();
  cout << " Racional c=c+a\n";

  c.simplifica();
  cout << "Racional c=c+a irreducible " << c << endl;

  e.asignar(6,4);
  f.asignar(3,2);
  g.asignar(3,5);

  cout << e << " Racional e 6/4\n";
  f.print();
  cout << " Racional f 3/2\n";
  g.print();
  cout << " Racional g 3/5\n";

  if (f.comparar(e)) 
    cout << "f y e son iguales\n";
  else
    cout << "f y e no son iguales\n";

  if
    (f==g) cout << "f y g son iguales\n";
  else
    cout << "f y g no son iguales\n";

  cout << "Introduzca el primer racional usando formato (r/i):" << endl;
  cin >> w;
  cout << "Introduzca el segundo racional usando formato (r/i):" << endl;
  cin >> z;
  cout << "La suma es " << w+z << endl;
  cout << "El producto es " << w*z << endl;
  return 0;
}
