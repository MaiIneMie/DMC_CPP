#ifndef KLIENTMATLAB_H
#define KLIENTMATLAB_H

#include <winsock2.h>
#include <string>
#include "ObiektBaza.h"

// Klasa dziedziczy po ObiektBaza
class KlientMATLAB : public ObiektBaza 
{
    private:
    int D, kroki;
    double y_k;

    // Stworzenie socketu
    SOCKET sock;

    public:
    //Konstruktor
    KlientMATLAB(const std::string& adres_ip, int port, int D, int kroki);

    double krok_online(double u_k) override;
    void reset() override
    {
    // Serwer MATLAB zarządza stanem obiektu po swojej stronie, reset nie wymaga komunikacji sieciowej.
    };
    double get_stan() const override
    {
        return y_k;
    };

    // Destruktor
    ~KlientMATLAB() 
    {
    // Zamknięcie połączenia i czyszczenie
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }
    WSACleanup();
    };
};

#endif