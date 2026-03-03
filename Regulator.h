#ifndef REGULATOR_H
#define REGULATOR_H

#include <Eigen/Dense>
#include "ObiektBaza.h"

class Regulator
{
    private:
    int D, N, Nu;        // horyzonty: dynamiki, predykcji, sterowania
    double alpha;        // waga błędu wyjścia
    double beta;         // waga przyrostów
    Eigen::MatrixXd M;   // macierz dynamiczna (N×Nu)
    Eigen::MatrixXd Mp;  // macierz przeszłości (N×(D-1))
    Eigen::MatrixXd K;   // macierz wzmocnień (Nu×N)
    ObiektBaza& obj;     // Wskaźnik do obiektu
    Eigen::VectorXd s;   // Macierz odpowiedzi skokowej

    // Stan regulatora
    double y_k = 0.0;   // obecne wyjście
    double u_k = 0.0;   // obecne sterowanie
    Eigen::VectorXd v;  // historia przyrostów (długość D-1)

    // Ograniczenia regulacji
    double u_min;
    double u_max;
    double dv_min;
    double dv_max;

    // Metody
    Eigen::VectorXd generuj_s(int D);
    // Funkcje pomocnicze do macierzy
    void oblicz_M();
    void oblicz_Mp();
    void oblicz_K();
    void oblicz_macierze(); // Macierze
    double ogranicz(double wartosc, double min, double max); // Ograniczenia

    public:
    // Inicjacja
    Regulator(int d, int n, int nu, double a, double b, double u_mi, double u_ma, double dv_mi, double dv_ma, ObiektBaza& obj);

    void krok_regulacji(double y_k, double yzad_k); // Jeden krok regulacji
    double get_u_k() const { return u_k; } // Getter dla Symulacja
};

#endif
