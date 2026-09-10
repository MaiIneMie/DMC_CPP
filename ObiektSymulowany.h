#ifndef OBIEKTYSYMULOWANY_H
#define OBIEKTYSYMULOWANY_H

#include <vector>
#include <stdexcept>
#include "ObiektBaza.h"

// Klasa dziedziczy po ObiektBaza
class ObiektSymulowany : public ObiektBaza {
    private:
    double a, b, y_k;
    int d, start, rozmiar; // start - indeks najstarszej próbki; rozmiar - długość bufora
    std::vector<double> bufor_u;

    public:
    //Konstruktor
    ObiektSymulowany(double a, double b, int d);
    // Symulacja kroku
    double krok_online(double u_k) override; // Implementacja metody wirtualnej

    void reset() override
    {
        std::fill(bufor_u.begin(), bufor_u.end(), 0.0); // Wyzerowanie bufora sterowania
        start = 0;  // Ustawienie indeksu początku bufora
        y_k = 0.0;  // Reset stanu wyjścia.
    };
    double get_stan() const override
    {
       return y_k;
    };

};

#endif