#ifndef TCP_H
#define TCP_H

#include <winsock2.h>
#include <stdexcept>
#include <string>

// Wysłanie dokładnie 'rozmiaru' bajtów z bufora 'dane' do socketu 'sock'.
inline void wyslij_wszystko(SOCKET sock, const char* dane, int rozmiar)
{
    // Obsługa wyjątków niepoprawnego rozmiaru
    if (rozmiar < 0)
    {
        throw std::invalid_argument("Rozmiar nie moze byc ujemny.");
    }
    if (rozmiar == 0)
    {
        return;
    }

    int wyslane = 0;
    while (wyslane < rozmiar)
    {
        int wyslane_teraz = send(
            sock,
            dane + wyslane,       // przesuwanie  po buforze, zaczęcie od 0 (dane); przesuniecie wskaznika w buforze o juz wyslane bajty
            rozmiar - wyslane,    // policzenie danych pozostałych do przesłania
            0                     // brak flag specjalnych
        );

        // Wyrzucenie std::runtime_error przy błędzie sieci lub zamknięciu połączenia.
        if (wyslane_teraz == SOCKET_ERROR)
        {
            throw std::runtime_error(
                "Blad wysylania TCP, kod: " + std::to_string(WSAGetLastError()) 
            );
        }

        if (wyslane_teraz == 0)
        {
            throw std::runtime_error(
                "Polaczenie zostalo zamkniete w trakcie wysylania."
            );
        }

        wyslane += wyslane_teraz;
    }
}

// Odebranie dokładnie 'rozmiaru' bajtów do bufora 'dane' z socketu 'sock'.
inline void odbierz_wszystko(SOCKET sock, char* dane, int rozmiar)
{
    // Obsługa wyjątków niepoprawnego rozmiaru
    if (rozmiar < 0)
    {
        throw std::invalid_argument("Rozmiar nie moze byc ujemny.");
    }
    if (rozmiar == 0)
    {
        return;
    }

    int odebrane = 0;
    while (odebrane < rozmiar)
    {
        int odebrane_teraz = recv(
            sock,
            dane + odebrane,
            rozmiar - odebrane,
            0
        );

        // Wyrzucenie std::runtime_error przy błędzie sieci lub zamknięciu połączenia.
        if (odebrane_teraz == SOCKET_ERROR)
        {
            throw std::runtime_error(
                "Blad odbierania TCP, kod: " + std::to_string(WSAGetLastError())
            );
        }
        if (odebrane_teraz == 0)
        {
            throw std::runtime_error(
                "Polaczenie zamkniete przez druga strone w trakcie odbioru."
            );
        }

        odebrane += odebrane_teraz;
    }
}

#endif