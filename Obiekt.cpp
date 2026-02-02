#include "Obiekt.h"

//Konstruktor
Obiekt::Obiekt(double a, double b, int d)
: a(a), b(b), d(d), y_k(0.0) 
{
// Utworzenie bufora o rozmiarze o 1 większym niż d
bufor_u.resize (d+1,0.0);
}


// Symulacja kroku
double Obiekt::krok_online(double u_k)
{
// Przesunięcie wartości budora (usunięcie pierwszego, najstarszego elementu i wpisanie najnowszego na koniec)
bufor_u.erase(bufor_u.begin());
bufor_u.push_back(u_k);

// Wzięcie najstarszego (pierwszego) elementu z bufora jako nowe sterowanie
double u_d = bufor_u[0];

// Wykonanie równania różnicowego
double y_k1 = a * y_k + b * u_d;

// Zapisanie wyniku równania jako nowe (obecne) wyjście
y_k = y_k1;

// Zwrócenie wyniku funkcji
return y_k1;
}
