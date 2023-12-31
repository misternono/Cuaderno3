/* Prueba:
     - Borrar, Nodos
*/

#include <iostream>
#include "tavlcom.h"
#include "tcomplejo.h"
#include "tvectorcom.h"
using namespace std;

int
main(void)
{
  TAVLCom a;
  TComplejo c;

  for(int i = 1; i <= 1000; i++)
  {
    //cout <<i<<endl;
    c.Re(i);
    c.Im(i);
    //cout << a <<endl;
    a.Insertar(c);
  }

  cout << "Nodos: " << a.Nodos() << endl;

  for(int i = 1; i <= 1000; i++)
  {
    c.Re(i);
    c.Im(i);
    a.Borrar(c);
  }

  cout << "Nodos: " << a.Nodos() << endl;
}
