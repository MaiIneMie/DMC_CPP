#ifndef OBIEKTYSYMULOWANY_H
#define OBIEKTYSYMULOWANY_H

#include <vector>
#include <stdexcept>
#include "ObiektBaza.h"

// Klasa dziedziczy po ObiektBaza
class ObiektSymulowany : public ObiektBaza {
    private:
    double a, b, y_k;
    int d, start, rozmiar; // start i rozmiar - dla krok_online
    std::vector<double> bufor_u;

    public:
    //Konstruktor
    ObiektSymulowany(double a, double b, int d);
    // Symulacja kroku
    double krok_online(double u_k) override; // Nadpisanie metody z ObiektBaza

    void reset() override
    {
        std::fill(bufor_u.begin(), bufor_u.end(), 0.0); // Wypełnienie wektora bufor zerami
    };
    double get_stan() const override
    {
       return bufor_u[start];
    };


};

#endif