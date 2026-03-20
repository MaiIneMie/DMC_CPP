#include "ObiektSymulowany.h"

//Konstruktor
ObiektSymulowany::ObiektSymulowany(double a, double b, int d)
: a(a), b(b), d(d), y_k(0.0), rozmiar(d+1), start(0)
{
if (d < 1)
{
throw std::invalid_argument("Opóźnienie musi być większe lub równe 1");
}
if (b == 0)
{
throw std::invalid_argument("Współczynnik b musi być różny od 0 (wpływ sterowania).");
}
// Utworzenie bufora o rozmiarze o 1 większym niż d
bufor_u.resize (rozmiar,0.0);
}

// Symulacja kroku
double ObiektSymulowany::krok_online(double u_k)
{

// Przesunięcie wartości bufora (usunięcie pierwszego, najstarszego elementu i wpisanie najnowszego na koniec)
bufor_u[start] = u_k;          // nadpisanie najstarszy element
start = (start + 1) % rozmiar; // przesunięcie wskaźnika o jedno miejsce dalej
double u_d = bufor_u[start];   // najstarsza wartość to teraz start

// Wykonanie równania różnicowego
double y_k1 = a * y_k + b * u_d;

// Zapisanie wyniku równania jako nowe (obecne) wyjście
y_k = y_k1;

// Zwrócenie wyniku funkcji
return y_k;
}
