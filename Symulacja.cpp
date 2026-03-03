#include "Symulacja.h"

// Konstruktor
Symulacja::Symulacja(int kroki, double yzad, ObiektBaza& obj, Regulator& reg)
: kroki(kroki), yzad(yzad), obj(obj), reg(reg)
{
    y_historia.resize(kroki);
    u_historia.resize(kroki);

}
// Uruchomienie symulacji
void Symulacja::uruchom()
{

}

// Zapis do pliku
void Symulacja::zapisz_csv(const std::string& nazwa_pliku)
{

}