#ifndef _tvectorcom
#define _tvectorcom
#include "tcomplejo.h"
#include <iostream>


class TVectorCom
{
    private:
        TComplejo *c;
        int tamano;
    public:
        // Constructor por defecto
        TVectorCom ();
        // Constructor a partir de un tamaño
        TVectorCom (int tam);
        // Constructor de copia
        TVectorCom (TVectorCom & tvcom);
        // Destructor
        ~TVectorCom ();
        // Sobrecarga del operador asignación
        TVectorCom & operator=(const TVectorCom & tvcom);

        // Sobrecarga del operador igualdad
        bool operator==(const TVectorCom &tvcom) const;
        // Sobrecarga del operador desigualdad
        bool operator!=( TVectorCom &tvcom);
        // Sobrecarga del operador corchete (parte IZQUIERDA)
        TComplejo & operator[](int pos);
        // Sobrecarga del operador corchete (parte DERECHA)
        TComplejo operator[](int pos) const;
        // Tamaño del vector (posiciones TOTALES)
        int Tamano();
        // Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
        int Ocupadas();
        // Devuelve TRUE  si existe el TComplejo en el vector
        bool ExisteCom(const TComplejo &comp) const;
        // Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL IGUAL O POSTERIOR al argumento
        void MostrarComplejos(double arg);
        // REDIMENSIONAR el vector de TComplejo
        bool  Redimensionar(int dim);

        friend std::ostream & operator<<(std::ostream &, const TVectorCom &);
};
#endif