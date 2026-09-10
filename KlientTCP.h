#ifndef KLIENTTCP_H
#define KLIENTTCP_H

#include <string>
#include <unistd.h>
#include "ObiektBaza.h"

// Klasa dziedziczy po ObiektBaza
class KlientTCP : public ObiektBaza 
{
    private:
    int D, kroki;
    double y_k;

    // Stworzenie socketu
    int sock;

    public:
    //Konstruktor
    KlientTCP(const std::string& adres_ip, int port, int D, int kroki);

    double krok_online(double u_k) override;
    void reset() override
    {
    // Brak operacji po stronie klienta; serwer resetuje zdalny obiekt po odebraniu D próbek odpowiedzi skokowej.
    };
    double get_stan() const override
    {
        return y_k;
    };

    // Destruktor
    ~KlientTCP();
};

#endif