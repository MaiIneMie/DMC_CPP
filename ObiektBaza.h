#ifndef OBIEKTBAZA_H
#define OBIEKTBAZA_H

#include <Eigen/Dense>

class ObiektBaza {
public:
    virtual double krok_online(double u_k) = 0; // Deklaracja
    virtual void reset() = 0;
    virtual double get_stan() const = 0;

    // Metoda dla generacji odpowiedzi skokowej
    Eigen::VectorXd generuj_s(int D)
    {   
        reset(); // Wyczyszczenie pamięci dla obiektu dla bezpieczeństwa
        Eigen::VectorXd s = Eigen::VectorXd::Zero(D); // Utworzenie wektora s i wypełnienie zerami
        for (int i = 0; i < D; i++)
        {
            s(i) = krok_online(1.0); // Generacja odpowiedzi dla skoku jednostkowego
        }
        reset(); // Wyczyszczenie pamięci dla obiektu dla czystego startu regulacji
        return s;
    }
    virtual ~ObiektBaza() {}  // Destruktor
};

#endif