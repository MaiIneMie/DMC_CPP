#include "Symulacja.h"
#include <fstream>

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
double y_k = 0.0;

for(int k = 0; k < kroki; k++)
{
    // Obliczenie sterowania
    reg.krok_regulacji(y_k, yzad);

    // Reakcja obiektu (aktualizacja)
    double y_nowe = obj.krok_online(reg.get_u_k());

    // Zapis do historii
    y_historia[k] = y_nowe;
    u_historia[k] = reg.get_u_k();
    
    // Aktualizaja y na kolejny krok
    y_k = y_nowe;

}

}

// Zapis do pliku
void Symulacja::zapisz_csv(const std::string& nazwa_pliku)
{
std::ofstream plik(nazwa_pliku);
plik << "k,y,u\n";  // nagłówek

for (int k = 0; k < kroki; k++) {
    plik << k << "," 
         << y_historia[k] << "," 
         << u_historia[k] << "\n";
}

plik.close();
std::cout << "Wyniki zapisane do: wyniki_dmc.csv" << std::endl;
}