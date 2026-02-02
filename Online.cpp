#include "Online.h"

void Online::krok(Stan& stan, const Parametry& param, const Offline& off, const Ograniczenia& ogr, double y_k, double yzad_k) 
{
    // Wektor wartości zadanych Yzad (N elementów = N wierszy)
    Eigen::VectorXd Yzad = Eigen::VectorXd::Constant(param.N, yzad_k);

    // Wektor wolnej odpoweidzi z przeszłością Y0 = y_k + Mp*v
    Eigen::VectorXd Y0 = Eigen::VectorXd::Constant(param.N, y_k) + off.Mp * stan.v;

    // Wektor błędu E = Yzad - Y0
    Eigen::VectorXd E = Yzad - Y0;

    // Wektor przyrostów sterowania v = K * E
    Eigen::VectorXd v = off.K * E;

    // Pobranie pierwszego elementu z tablicy przyrostów
    double v_k = v(0);

    // Ograniczenie przyrostu
    v_k = ogranicz(v_k, ogr.dv_min, ogr.dv_max);

    // Obliczenie nowego sterowania
    double u_k = stan.u_k + v_k;

    // Ograniczenie sterowanie
    u_k = ogranicz(u_k, ogr.u_min, ogr.u_max);

    // Aktualizacja stanu
    stan.u_k = u_k;
    stan.y_k = y_k;

    // Aktualizacja historii przyrostów
    for (int i = stan.v.size() - 1; i > 0; i--) // Zaczynając od końca w dół
    {
        stan.v(i) = stan.v(i - 1); // Przypisanie elementowi wartości o jeden mniejszej (28 skopiowany z 27 itd)
    }
    stan.v(0) = v_k; // Element pierwszy to najnowszy przyrost


}

// Funkcja utrzymująca daną wartość w odpowiednim zakresie
double Online::ogranicz(double wartosc, double min, double max)
{
    if (wartosc < min) return min;
    if (wartosc > max) return max;
    return wartosc;

}