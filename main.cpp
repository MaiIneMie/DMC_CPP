#include <iostream>
#include <vector>
#include <fstream>

#include "ObiektSymulowany.h"
#include "Symulacja.h"

int main()
{
    std::cout << "=== DMC w C++ - Symulacja ===" << std::endl << std::endl;

    // === SCENARIUSZ A: Model idealny ===
    std::cout << "Scenariusz A: Model idealny." << std::endl;

    // 1. Utworzenie instancji regulatora i wygenerowanie odpowiedzi skokowej
    Regulator reg_A (30, 10, 5, 1.0, 1.0, 0.0, 1.0, -0.2, 0.2, 0.8351, 0.2713, 2);

    // 2. Stworzenie obiektu sterowanego (takiego samego jak ten generujący s)
    ObiektSymulowany obj_A (0.8351, 0.2713, 2);

    // 3. Stworzenie instancji symulacji
    Symulacja sym_A (100, 1.0, obj_A, reg_A);

    // 4. Uruchomienie pętli regulacji
    sym_A.uruchom();

    // 5. Zapisanie wyników do pliku csv
    sym_A.zapisz_csv("wyniki_dmc_A.csv");
    
    std::cout << "Scenariusz A zakończony." << std::endl << std::endl;



    // === SCENARIUSZ B: Model niedokładny ===
    std::cout << "Scenariusz B: Model niedokładny." << std::endl;

    // 1. Utworzenie instancji regulatora i wygenerowanie odpowiedzi skokowej
    Regulator reg_B (30, 10, 5, 1.0, 1.0, 0.0, 1.0, -0.2, 0.2, 0.8, 0.2, 2);

    // 2. Stworzenie obiektu sterowanego (takiego samego jak ten generujący s)
    ObiektSymulowany obj_B (0.8351, 0.2713, 2);

    // 3. Stworzenie instancji symulacji
    Symulacja sym_B (100, 1.0, obj_B, reg_B);

    // 4. Uruchomienie pętli regulacji
    sym_B.uruchom();

    // 5. Zapisanie wyników do pliku csv
    sym_B.zapisz_csv("wyniki_dmc_B.csv");
    
    std::cout << "Scenariusz B zakończony." << std::endl << std::endl;
}