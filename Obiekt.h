#ifndef OBIEKT_H
#define OBIEKT_H

#include <vector>

class Obiekt {
    private:
    double a, b, y_k;
    int d;
    std::vector<double> bufor_u;

    public:

    //Konstruktor
    Obiekt(double a, double b, int d);
    // Symulacja kroku
    double krok_online(double u_k);

};

#endif