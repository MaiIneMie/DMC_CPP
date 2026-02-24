#ifndef PARAMETRY_H
#define PARAMETRY_H

#include <Eigen/Dense>
#include "ObiektBaza.h"

class Parametry {

    private:
    // Prywatna funkcja do generowania s (używana tylko wewnętrznie)
    Eigen::VectorXd generuj_s(ObiektBaza& obj, int D);
    void oblicz_offline();

    public:
    // Horyzonty
    int D, N, Nu;

    // Wagi
    double alpha;  // waga błędu wyjścia
    double beta;   // waga przyrostów

    // Odpowiedź skokowa
    Eigen::VectorXd s;

    // Konstruktor
    Parametry(int d, int n, int nu, double a, double b, ObiektBaza& obj);
};

#endif