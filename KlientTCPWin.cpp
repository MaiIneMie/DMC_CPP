#include "KlientTCPWin.h"
#include "TCPWin.h"

#include <iostream>
#include <ws2tcpip.h>

KlientTCPWin :: KlientTCPWin(const std::string& adres_ip, int port, int D, int kroki)
: D(D), kroki(kroki), y_k(0.0), sock(INVALID_SOCKET)
{
    // Inicjalizacja Winsock
    WSADATA wsaData;

    // Obsługa wyjątku startu
    int wynik = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (wynik != 0)
    {
        throw std::runtime_error(
            "Blad WSAStartup, kod: " + std::to_string(wynik)
        );
    }

    // Utworzenie gniazda TCP
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Sprawdzenie poprawności utworzenia gniazda
    if (sock == INVALID_SOCKET)
    {
        int kod = WSAGetLastError();
        WSACleanup();
        throw std::runtime_error(
            "Blad tworzenia socketu, kod: " + std::to_string(kod)
        );
    }

    // Adres serwera
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    // Konwersja i weryfikacja adresu IPv4
    int wynik_ip = inet_pton(AF_INET, adres_ip.c_str(), &server.sin_addr);
    if (wynik_ip != 1)
    {
        closesocket(sock);
        WSACleanup();
        throw std::runtime_error(
            "Bledny adres IP: " + adres_ip
        );
    }

    // Połączenie
    // Obsługa wyjątku połączenia
    if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        int kod = WSAGetLastError();
        closesocket(sock);
        WSACleanup();
        throw std::runtime_error(
            "Blad polaczenia, kod: " + std::to_string(kod)
        );
    }

    try
    {
    // Konwersja parametrów do formatu double oczekiwanego przez serwer MATLAB
    double D_d = static_cast<double>(D);
    double kroki_d = static_cast<double>(kroki);
    // Wysłanie długości odpowiedzi skokowej D, a następnie liczby kroków symulacji
    wyslij_wszystko(sock, (const char*)&D_d, sizeof(D_d));
    wyslij_wszystko(sock, (const char*)&kroki_d, sizeof(kroki_d));
    }
    catch (...)
    {
    closesocket(sock);
    WSACleanup();
    throw;
    }
};

double KlientTCPWin::krok_online(double u_k)
{
wyslij_wszystko(sock, (const char*)&u_k, sizeof(u_k));
odbierz_wszystko(sock, (char*)&y_k, sizeof(y_k));
return y_k;
};
