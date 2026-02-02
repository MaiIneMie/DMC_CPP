#include <iostream>
#include <vector>
#include <fstream>

#include "Obiekt.h"
#include "Offline.h"
#include "Ograniczenia.h"
#include "Online.h"
#include "Parametry.h"
#include "Stan.h"

int main()
{
    std::cout << "=== DMC w C++ - Symulacja ===" << std::endl << std::endl;

    // Podanie parametrów dla symulacji
    const int kroki = 100;
    const double yzad = 1.0;


    // === SCENARIUSZ A: Model idealny ===
    std::cout << "Scenariusz A: Model idealny." << std::endl;

    // 1. Stworzenie obiektu do generacji odpowiedzi skokowej s
    Obiekt obj_s_A (0.8351, 0.2713, 2);

    // 2. Przekazanie parametrów do obiektu generowania s
    Parametry param_A (30, 10, 5, 1.0, 1.0, obj_s_A);

    // 3. Obliczenia wstępne (M, Mp, K)
    Offline off_A (param_A);

    // 4. Obliczenie stanu początkowego układu
    Stan stan_A (param_A.D);

    // 5. Wprowadzenie ograniczeń sterowania i przyrostów sterowania
    Ograniczenia ogr_A (0.0, 1.0, -0.2, 0.2);

    // 6. Stworzenie obiektu sterowanego (takiego samego jak ten generujący s)
    Obiekt obj_A (0.8351, 0.2713, 2);

    // 7. Stworzenie instancji pętli regulatora
    Online online_A;

    // 8. Stworzenie wektorów na historię wyników odpowiedzi i sterowań
    std::vector<double> y_historia_A(kroki);
    std::vector<double> u_historia_A(kroki);

    // 9. Wykonanie właściwej pętli regulacji
    for (int k = 0; k < kroki; k++)
    {
        online_A.krok(stan_A, param_A, off_A, ogr_A, stan_A.y_k, yzad); // Obliczenie sterowania
        double y_nowe = obj_A.krok_online(stan_A.u_k); // Obliczenie reakcji obiektu

        // Zapisanie nowego sterowania i wyjścia do historii
        y_historia_A[k] = y_nowe;
        u_historia_A[k] = stan_A.u_k;

        stan_A.y_k = y_nowe; // Aktualizacja y dla kolejnego kroku symulacji
    }

    std::cout << "Scenariusz A zakończony." << std::endl << std::endl;



    // === SCENARIUSZ B: Model niedokładny ===
    std::cout << "Scenariusz B: Model niedokładny." << std::endl;

    // 1. Stworzenie obiektu do generacji odpowiedzi skokowej
    Obiekt obj_s_B (0.8, 0.2, 2);

    // 2. Przekazanie parametrów do obiektu generowania s
    Parametry param_B (30, 10, 5, 1.0, 1.0, obj_s_B);

    // 3. Obliczenia wstępne (M, Mp, K)
    Offline off_B(param_B);

    // 4. Obliczenia stanu początkowego układu
    Stan stan_B (param_B.D);

    // 5. Wprowadzenie ograniczeń sterowania i przyrostów sterowania
    Ograniczenia ogr_B (0.0, 1.0, -0.2, 0.2);

    // 6. Stworzenie obiektu sterowanego (innego niż generującego s)
    Obiekt obj_B(0.8351, 0.2713, 2);

    // 7. Stworzenie instancji pętli regulatora
    Online online_B;

    // 8. Stworzenie wektorów dla historii wyników odpowiedzi i sterowań
    std::vector<double> y_historia_B(kroki);
    std::vector<double> u_historia_B(kroki);

    // 9. Wykonanie właściwej pętli regulacji
    for (int k = 0; k < kroki; k++)
    {
        online_B.krok(stan_B, param_B, off_B, ogr_B, stan_B.y_k, yzad); // Obliczenie sterowania
        double y_nowe = obj_B.krok_online(stan_B.u_k); // Obliczenie reakcji obiektu

        // Zapisanie nowego sterowania i wyjścia do historii
        y_historia_B[k] = y_nowe;
        u_historia_B[k] = stan_B.u_k;

        stan_B.y_k = y_nowe; // Aktualizacja y dla kolejnego kroku symulacji
    }

    std::cout << "Scenariusz B zakończony." << std::endl << std::endl;

    // === WYNIKI ===
    std::cout << "=== PORÓWNANIE WYNIKÓW ===" << std::endl << std::endl;

    std::cout << "Wybrane kroki symulacji (co 10 kroków):" << std::endl;
    std::cout << "k\tA: y(k)\tA: u(k)\t|\tB: y(k)\tB: u(k)" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;

    for (int k = 0; k < kroki; k += 10) {
        std::cout << k << "\t" 
                << y_historia_A[k] << "\t" 
                << u_historia_A[k] << "\t|\t"
                << y_historia_B[k] << "\t" 
                << u_historia_B[k] << std::endl;
    }

    std::cout << std::endl << "Wartość zadana: " << yzad << std::endl;
    std::cout << "Ostatnie wartości:" << std::endl;
    std::cout << "A: y=" << y_historia_A[kroki-1] << ", u=" << u_historia_A[kroki-1] << std::endl;
    std::cout << "B: y=" << y_historia_B[kroki-1] << ", u=" << u_historia_B[kroki-1] << std::endl;

// ZAPIS DO PLIKU CSV
std::ofstream plik("wyniki_dmc.csv");
plik << "k,y_A,u_A,y_B,u_B\n";  // nagłówek

for (int k = 0; k < kroki; k++) {
    plik << k << "," 
         << y_historia_A[k] << "," 
         << u_historia_A[k] << ","
         << y_historia_B[k] << "," 
         << u_historia_B[k] << "\n";
}

plik.close();
std::cout << "Wyniki zapisane do: wyniki_dmc.csv" << std::endl;
}