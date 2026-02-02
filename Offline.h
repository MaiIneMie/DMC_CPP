#ifndef OFFLINE_H
#define OFFLINE_H

#include <Eigen/Dense>
#include "Parametry.h"

class Offline
{
    public:
    Eigen::MatrixXd M;   // macierz dynamiczna (N×Nu)
    Eigen::MatrixXd Mp;  // macierz przeszłości (N×(D-1))
    Eigen::MatrixXd K;   // macierz wzmocnień (Nu×N)

    // Konstruktor - oblicza wszystkie macierze
    Offline(const Parametry& param);

    private:
    // Funkcje pomocnicze (prywatne)
    void oblicz_M(const Eigen::VectorXd& s, int N, int Nu);
    void oblicz_Mp(const Eigen::VectorXd& s, int N, int D);
    void oblicz_K(int N, int Nu, double alpha, double beta);
};

#endif
