#ifndef SYMULACJA_H
#define SYMULACJA_H

#include <Eigen/Dense>
#include "ObiektBaza.h"
#include "Regulator.h"

#include <vector>
#include <string>

class Symulacja
{
    private:
    // Podanie parametrów dla symulacji (liczba kroków i wartość zadana)
    const int kroki;
    const double yzad;
    ObiektBaza& obj; // Referencja do obiektu
    Regulator& reg; // Referencja do regulatora
    // Historia dla y oraz u
    std::vector<double> y_historia;
    std::vector<double> u_historia;

    public:
    // Inicjacja
    Symulacja(int kroki, double yzad, ObiektBaza& obj, Regulator& reg);
    // Uruchomienie symulacji
    void uruchom();
    // Zapis do pliku
    void zapisz_csv(const std::string& nazwa_pliku);

};

#endif