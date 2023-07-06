#include "../include/tvectorcom.h"
    
    // Constructor por defecto
    TVectorCom::TVectorCom ()
    {
        this->tamano = 0;
        this->c = (TComplejo*) malloc(sizeof(TComplejo));;
    }
    // Constructor a partir de un tamaño
    TVectorCom::TVectorCom (int tam)
    {
        if(tam < 0) tam = 0;
        this->tamano = tam;
        if (tam > 0)
            this->c = (TComplejo*) malloc(this->tamano * sizeof(TComplejo));
        for(int i = 0; i < this->tamano; i++) 
        {
            *(this->c +i) = *new TComplejo();
        }
    }
    // Constructor de copia
    TVectorCom::TVectorCom (TVectorCom & tvcom)
    {
        this->tamano = tvcom.tamano;
        this->c = (TComplejo*) malloc(this->tamano * sizeof(TComplejo));
        for(int i = 0; i < this->tamano; i++) 
        {
            *(this->c +i) = *(tvcom.c + i);
        }
    }
    // Destructor
    TVectorCom::~TVectorCom ()
    {
        //std::cout << this->c << std::endl;
        this->tamano = 0;
        if (c != NULL)free(c);
        c = NULL;
    }
    // Sobrecarga del operador asignación
    TVectorCom & TVectorCom::operator=(const TVectorCom & tvcom)
    {
        if (this != &tvcom) { // Check for self-assignment /////////////////////////////
            this->tamano = tvcom.tamano;
            this->c = (TComplejo*) malloc(this->tamano * sizeof(TComplejo));
            for(int i = 0; i < this->tamano; i++) 
            {
                *(this->c +i) = *(tvcom.c + i);
            }
        }
        
        return *this;
    }

    // Sobrecarga del operador igualdad
    bool TVectorCom::operator==(const TVectorCom & tvcom) const
    {
        if(this->tamano != tvcom.tamano) return false;
        for(int i = 0; i < this->tamano; i++) 
        {
            if (*(this->c +i) != *(tvcom.c + i)) return false;
        }
        return true;
    }
    
    // Sobrecarga del operador desigualdad
    bool TVectorCom::operator!=( TVectorCom & tvcom)
    {
        if(this->tamano != tvcom.tamano) return true;
        for(int i = 0; i < this->tamano; i++) 
        {
            if (*(this->c + i) != *(tvcom.c + i)) return true;
        }
        return false;
    }
    // Sobrecarga del operador corchete (parte IZQUIERDA)
    TComplejo & TVectorCom::operator[](int pos)
    {
        // Si la posición está dentro del rango del vector
        if (pos >= 1 && pos <= tamano) {
            return c[pos-1];
        } else {
            // Si la posición está fuera del rango del vector
            TComplejo *complejoVacio = new TComplejo();
            return *complejoVacio;
        }
    }
    // Sobrecarga del operador corchete (parte DERECHA)
    TComplejo TVectorCom::operator[](int pos) const
    {
        if (pos >= 1 && pos <= tamano) {
            return c[pos-1];
        } else {
            // Si la posición está fuera del rango del vector
            TComplejo complejoVacio;
            return complejoVacio;
        }
    }
    // Tamaño del vector (posiciones TOTALES)
    int TVectorCom::Tamano()
    {
        return tamano;
    }
    // Cantidad de posiciones OCUPADAS (TComplejo NO VACIO) en el vector
    int TVectorCom::Ocupadas()
    {
        int ocup = 0;
        TComplejo *vacio = new TComplejo();
        for(int i = 0; i < this->tamano; i++) 
        {
            if (*(this->c + i) != *vacio) ocup++;
        }
        return ocup;
    }
    // Devuelve TRUE  si existe el TComplejo en el vector
    bool TVectorCom::ExisteCom(const TComplejo & comp) const
    {
        for(int i = 0; i < this->tamano; i++) 
        {
            if (*(this->c + i) == comp) return true;
        }
        return false;
    }
    // Mostrar por pantalla los elementos TComplejo del vector con PARTE REAL IGUAL O POSTERIOR al argumento
    void TVectorCom::MostrarComplejos(double real)
    {
        std::cout << "[";
        for (int i = 0; i < tamano; i++) {
            if (c[i].Re() >= real) {
                std::cout << c[i];
                if (i != tamano - 2) std::cout << ", ";
            }
        }
        std::cout << "]";
    }
    // REDIMENSIONAR el vector de TComplejo
    bool TVectorCom::Redimensionar(int dim)
    {
        if (dim <= 0) return false;

        // No hay que hacer nada si la dimension es igual a la actual
        if (dim == this->tamano) return false;

        // Reservar memoria para el nuevo vector
        TComplejo *nuevo_c = (TComplejo*) malloc(dim * sizeof(TComplejo));

        // Copiar los elementos del vector actual al nuevo vector
        int n = (dim > this->tamano) ? dim : this->tamano;

        for (int i = 0; i < n; i++) {
            if(i < this->tamano){
                *(nuevo_c + i) = *(this->c + i);
            }
            else
            {
                *(nuevo_c + i) = *new TComplejo();
            }
        }
        
        // Liberar memoria del vector actual
        try{
            free(this->c);
        }
        catch(int e){

        }

        // Asignar el nuevo vector al vector actual
        this->tamano = dim;
        this->c = nuevo_c;

        return true;
    }

    std::ostream & operator<<(std::ostream &os, const TVectorCom &tvcom)
    {
        os << "[";
        for(int i = 0; i < tvcom.tamano; i++){
            os << "(" << i + 1 << ") ";
            os << *(tvcom.c + i);
            if (i != tvcom.tamano -1 ) os << ", ";
        }
        os << "]";
        return os;
    }