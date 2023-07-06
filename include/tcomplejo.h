#ifndef _tcomplejo
#define _tcomplejo

#include <ostream>

class TComplejo
{
private:
    double re;
    double im;
public:
    TComplejo();
    TComplejo(double re);
    TComplejo(double re, double im);
    TComplejo(const TComplejo& complejo);
    TComplejo& operator= (const TComplejo& complejo);

    TComplejo operator+ (const TComplejo& complejo) const;
    TComplejo operator- (const TComplejo& complejo) const;
    TComplejo operator* (const TComplejo& complejo) const;
    TComplejo operator+ (double parte) const; 
    TComplejo operator- (double parte) const; 
    TComplejo operator* (double parte) const;

    bool operator== (const TComplejo& complejo) const; 
    bool operator!= (const TComplejo& complejo) const;
    double Re() const; // Devuelve PARTE REAL 
    double Im() const; // Devuelve PARTE IMAGINARIA
    void Re(double re); // Modifica PARTE REAL
    void Im(double im); // Modifica PARTE IMAGINARIA
    double Arg(void); // Calcula el Argumento (en Radianes) 
    double Mod(void); // Calcula el Módulo

    friend std::ostream & operator<<(std::ostream &, const TComplejo &);
    friend TComplejo operator+ (double , const TComplejo&); 
    friend TComplejo operator- (double , const TComplejo&); 
    friend TComplejo operator* (double , const TComplejo&);

    ~TComplejo();
};
#endif