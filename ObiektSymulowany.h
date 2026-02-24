#ifndef OBIEKTYMULOWANY_H
#define OBIEKTYMULOWANY_H

#include <vector>
#include "ObiektBaza.h"

// Klasa dziedziczy po ObiektBaza
class ObiektSymulowany : public ObiektBaza {
    private:
    double a, b, y_k;
    int d;
    std::vector<double> bufor_u;

    public:
    //Konstruktor
    ObiektSymulowany(double a, double b, int d);
    // Symulacja kroku
    double krok_online(double u_k) override; // Nadpisanie metody z ObiektBaza

};

#endif