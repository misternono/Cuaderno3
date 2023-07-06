
#include <stdlib.h>
#include <stdio.h>
#include <ostream>
#include "../include/tcomplejo.h"
#include <cmath>

using std::ostream;

    TComplejo::TComplejo()
    {
        this->re = 0;
        this->im = 0;
    }

    TComplejo::TComplejo(double re)
    {
        this->im = (double)0;
        this->re = (double)re;
    }

    TComplejo::TComplejo(double re, double im)
    {
        this->re = re;
        this->im = im;
    }

    TComplejo::TComplejo(const TComplejo& complejo)
    {
        this->re = complejo.re;
        this->im = complejo.im;
    }

    TComplejo& TComplejo::operator=(const TComplejo& complejo)
{
    if (this != &complejo) { // Check for self-assignment
        this->re = complejo.re;
        this->im = complejo.im;
    }
    return *this;
}
    TComplejo TComplejo::operator+ (const TComplejo& complejo) const
    {
        TComplejo com;
        com.re = re + complejo.re;
        com.im = im + complejo.im;
        return com;
        //return *new TComplejo(this->re + complejo.re, this->im+complejo.im);
    }

    TComplejo TComplejo::operator- ( const TComplejo& complejo) const
    {
        return *new TComplejo(this->re - complejo.re, this->im - complejo.im);
    }

    TComplejo TComplejo::operator* ( const TComplejo& complejo) const
    {
        return *new TComplejo(this->re * complejo.re, this->im * complejo.im);
    }

    TComplejo TComplejo::operator+ ( const double parte) const
    {
        return *new TComplejo(this->re + parte, this->im);
    }

    TComplejo TComplejo::operator- ( const double parte) const
    {
        return *new TComplejo(this->re - parte, this->im);
    }

    TComplejo TComplejo::operator* (const double parte) const
    {
        return *new TComplejo(this->re * parte, this->im * parte);
    }

    bool TComplejo::operator== (const TComplejo& complejo) const 
    {
        return (this->re == complejo.re && this->im == complejo.im);
    }

    bool TComplejo::operator!= (const TComplejo& complejo) const
    {
        return !(this->re == complejo.re && this->im == complejo.im);
    }

    double TComplejo::Re() const 
    {
        return this->re;
    }

    double TComplejo::Im() const 
    {
        return this->im;
    }

    void TComplejo::Re(double re)
    {
        this->re = re;
    }

    void TComplejo::Im(double im)
    {
        this->im = im;
    }

    double TComplejo::Arg(void)
    {
        return std::atan2(this->im, this->re);
    }

    double TComplejo::Mod(void)
    {
        return (double)sqrt(pow(this->re,2) + pow(this->im,2));
    }

    TComplejo::~TComplejo()
    {
        this->im = 0;
        this->re = 0;
    }

    std::ostream& operator<<(std::ostream& os, const TComplejo& c) {
        os << "(" << c.re << " " << c.im << ")";
        return os;
    }

    TComplejo operator+ (double parte, const TComplejo& complejo){
        return *new TComplejo(complejo.Re() + parte, complejo.Im());
    }
    TComplejo operator- (double parte, const TComplejo& complejo){
        return *new TComplejo(parte - complejo.Re(), 0 - complejo.Im());
    }
    TComplejo operator* (double parte, const TComplejo& complejo){
        return *new TComplejo(complejo.Re() * parte, complejo.Im() * parte);
    }