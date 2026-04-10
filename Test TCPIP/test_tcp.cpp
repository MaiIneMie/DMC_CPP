#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    // Inicjalizacja Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    // Stworzenie socketu
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    // Adres serwera (MATLAB na tym samym komputerze)
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    // Połączenie
    connect(sock, (sockaddr*)&server, sizeof(server));
    std::cout << "Połączono!" << std::endl;

    // Wysłanie liczby
    double wartosc = 3.14;
    send(sock, (char*)&wartosc, sizeof(wartosc), 0);
    std::cout << "Wysłano: " << wartosc << std::endl;

// Odbieranie odpowiedzi
    double odpowiedz;
    recv(sock, (char*)&odpowiedz, sizeof(odpowiedz), 0);
    std::cout << "Odebrano: " << odpowiedz << std::endl;

    Sleep(1000);
    closesocket(sock);
    WSACleanup();
    return 0;
}