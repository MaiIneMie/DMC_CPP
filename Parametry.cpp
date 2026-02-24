#include "Parametry.h"

    // Konstruktor
    Parametry::Parametry(int d, int n, int nu, double a, double b, ObiektBaza& obj)
    : D(d), N(n), Nu(nu), alpha(a), beta(b)
    {
      s = generuj_s(obj, D);
    }

    // Funkcja generująca odpowiedź skokową
    Eigen::VectorXd Parametry::generuj_s(ObiektBaza& obj, int D)
    {
      // Deklaracja wektora wypełnionego wartościami odpowiedzi skokowej (rozmiar D)
      Eigen::VectorXd s(D);

      // Symulacja działania obiektu na wywołanie wartośći skokowej 1
      for (int k = 0; k < D; k++)
      {
            s(k) = obj.krok_online(1.0);
      }

      // Zwrot wektora odpowiedzi skokowej
      return s;

    }