#include <iostream>
#include <vector>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "ObiektSymulowany.h"
#include "Symulacja.h"

#pragma comment(lib, "ws2_32.lib")

// Przypadek modelu wewnętrznego
void wariant(
    // Parametry dla regulatora
    int D, int N, int Nu, double alpha, double beta, double u_min, double u_max, double dv_min, double dv_max, double a_reg, double b_reg, int d_reg, 
    // Parametry dla obiektu (model wewnętrzny)
    double a_obj, double b_obj, double d_obj,
    // Parametry dla symulacji
    int kroki, double yzad, const std::string& nazwa_pliku)
{
    // 1. Utworzenie instancji regulatora i wygenerowanie odpowiedzi skokowej
    Regulator reg(D, N, Nu, alpha, beta, u_min, u_max, dv_min, dv_max, a_reg, b_reg, d_reg);
    // 2. Stworzenie obiektu sterowanego (takiego samego jak ten generujący s)
    ObiektSymulowany obj (a_obj, b_obj, d_obj);
    // 3. Stworzenie instancji symulacji
    Symulacja sym (kroki, yzad, obj, reg);
    // 4. Uruchomienie pętli regulacji
    sym.uruchom();
    // 5. Zapisanie wyników do pliku csv
    sym.zapisz_csv(nazwa_pliku);
}

// Przypadek modelu zewnętrznego z odczytem
void wariant(
    // Parametry dla regulatora
    int D, int N, int Nu, double alpha, double beta, double u_min, double u_max, double dv_min, double dv_max,
    // Parametry dla symulacji
    int kroki, double yzad, const std::string& nazwa_pliku)
{
    // Utworzenie wektora s o długości D
    Eigen::VectorXd s(D);
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

    // Konwersja wartości na double dla łatwiejszej integracji z MATLAB
    double D_d = (double)D;
    double kroki_d = (double)kroki;

    // Wysłanie liczby kroków i długości odpowiedzi skokowej
    send(sock, (char*)&D_d, sizeof(D_d), 0);
    std::cout << "Wysłano D o wartości: " << D_d << std::endl;
    send(sock, (char*)&kroki_d, sizeof(kroki_d), 0);
    std::cout << "Wysłano kroków: " << kroki_d << std::endl;

    // Zadanie wartości 1 na sterowanie dla odpowiedzi skokowej
    double u_s = 1.0;

    for (int i = 0; i < D; i++)
    {
        send(sock, (char*)&u_s, sizeof(u_s), 0);
    }

    // Odbieranie wektora s o długości D
    for (int i = 0; i < D; i++)
    {
        recv(sock, (char*)&s(i), sizeof(double), 0);
    }
    std::cout << "Odebrano wektor odpowiedzi skokowej." << std::endl;

    // Stworzenie regulatora z wektorem s
    Regulator reg(D, N, Nu, alpha, beta, u_min, u_max, dv_min, dv_max, s);

    // Utworzenie pomocniczych wektorów dla historii wejść i wyjść
    std::vector<double> y_historia;
    std::vector<double> u_historia;

    // Pętla regulacji
    for (int k = 0; k < kroki; k++)
    {
    // Wysłanie sterowania do MATLABa
    double u_k = reg.get_u_k();
    send(sock, (char*)&u_k, sizeof(u_k), 0);
    
    // Odebranie wyjścia obiektu
    double y_k;
    recv(sock, (char*)&y_k, sizeof(y_k), 0);
    
    // Krok regulacji
    reg.krok_regulacji(y_k, yzad);
    y_historia.push_back(y_k);
    u_historia.push_back(reg.get_u_k());
    }

    // Zapis wyników
    std::ofstream plik(nazwa_pliku);
    plik << "k,y,u\n";
    for (int k = 0; k < kroki; k++)
    {
        plik << k << "," << y_historia[k] << "," << u_historia[k] << "\n";
    }

    // Zamknięcie połączenia i czyszczenie
    closesocket(sock);
    WSACleanup();
}


int main()
{
    std::cout << "=== DMC w C++ - Symulacja ===" << std::endl << std::endl;

    // === SCENARIUSZ A: Model idealny ===
    std::cout << "Scenariusz A: Model idealny." << std::endl;

    wariant(
    // Parametry dla regulatora
    30, 10, 5, 1.0, 1.0, 0.0, 1.0, -0.2, 0.2, 0.8351, 0.2713, 2,
    // Parametry dla obiektu (model wewnętrzny)
    0.8351, 0.2713, 2,
    // Parametry dla symulacji
    100, 1.0, "wyniki_dmc_A.csv");
    
    std::cout << "Scenariusz A zakończony." << std::endl << std::endl;


    // === SCENARIUSZ B: Model niedokładny ===
    std::cout << "Scenariusz B: Model niedokładny." << std::endl;

     wariant(
    // Parametry dla regulatora
    30, 10, 5, 1.0, 1.0, 0.0, 1.0, -0.2, 0.2, 0.8, 0.2, 2,
    // Parametry dla obiektu (model wewnętrzny)
    0.8351, 0.2713, 2,
    // Parametry dla symulacji
    100, 1.0, "wyniki_dmc_B.csv");
    
    std::cout << "Scenariusz B zakończony." << std::endl << std::endl;

    // === SCENARIUSZ C: Model zewnętrzny (TCP/MATLAB) ===
    std::cout << "Scenariusz C: Model zewnętrzny przez TCP." << std::endl;

    wariant(
        // Parametry dla regulatora
        30, 10, 5, 1.0, 1.0, 0.0, 1.0, -0.2, 0.2,
        // Parametry dla symulacji
        100, 1.0, "wyniki_dmc_C.csv");
    std::cout << "Scenariusz C zakończony." << std::endl << std::endl;
}