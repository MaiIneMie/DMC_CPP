#ifndef KLIENTTCP_H
#define KLIENTTCP_H

#include <winsock2.h>
#include <string>
#include "ObiektBaza.h"

// Klasa dziedziczy po ObiektBaza
class KlientTCP : public ObiektBaza 
{
    private:
    int D, kroki;
    double y_k;

    // Stworzenie socketu
    SOCKET sock;

    public:
    //Konstruktor
    KlientTCP(const std::string& adres_ip, int port, int D, int kroki);

    double krok_online(double u_k) override;
    void reset() override
    {
    // Serwer zarządza stanem obiektu po swojej stronie, reset nie wymaga komunikacji sieciowej.
    };
    double get_stan() const override
    {
        return y_k;
    };

    // Destruktor
    ~KlientTCP() 
    {
    // Zamknięcie połączenia i czyszczenie
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }
    WSACleanup();
    };
};

#endif