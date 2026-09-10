#include <iostream>
#include <vector>
#include <fstream>

#include "ObiektSymulowany.h"
#include "Symulacja.h"
#include "KlientTCP.h"

// Wariant z wewnętrznym modelem regulatora
void wariant(
    // Parametry dla regulatora
    int D, int N, int Nu, double alpha, double beta, double u_min, double u_max, double dv_min, double dv_max, double a_reg, double b_reg, int d_reg, 
    // Parametry symulowanego obiektu sterowanego
    double a_obj, double b_obj, double d_obj,
    // Parametry dla symulacji
    int kroki, double yzad, const std::string& nazwa_pliku)
{
    // Utworzenie instancji regulatora i wygenerowanie odpowiedzi skokowej
    Regulator reg(D, N, Nu, alpha, beta, u_min, u_max, dv_min, dv_max, a_reg, b_reg, d_reg);
    // Utworzenie symulowanego obiektu sterowanego
    ObiektSymulowany obj (a_obj, b_obj, d_obj);
    // Stworzenie instancji symulacji
    Symulacja sym (kroki, yzad, obj, reg);
    // Uruchomienie pętli regulacji
    sym.uruchom();
    // Zapisanie wyników do pliku csv
    sym.zapisz_csv(nazwa_pliku);
}

// Wariant z zewnętrznym obiektem komunikującym się przez TCP
void wariant(
    // Parametry dla regulatora
    int D, int N, int Nu, double alpha, double beta, double u_min, double u_max, double dv_min, double dv_max,
    // Parametry dla symulacji
    int kroki, double yzad, const std::string& nazwa_pliku,
    // Parametry dla komunikacji
    const std::string& adres_pc)
{

    // Inicjalizacja komunikacji
    KlientTCP obj(adres_pc, 12345, D, kroki);

    // Utworzenie wektora s o długości D
    Eigen::VectorXd s = obj.generuj_s(D);

    // Stworzenie regulatora
    Regulator reg(D, N, Nu, alpha, beta, u_min, u_max, dv_min, dv_max, s);

    // Stworzenie instancji symulacji
    Symulacja sym (kroki, yzad, obj, reg);

    // Uruchomienie pętli regulacji
    sym.uruchom();

    // Zapisanie wyników do pliku csv
    sym.zapisz_csv(nazwa_pliku);
}


int main(int argc, char* argv[])
{
    // Adres PC, na którym działa serwer MATLAB.
    // Jeśli argument nie zostanie podany, używany jest adres 127.0.0.1 (localhost).
    std::string adres_pc = (argc > 1) ? argv[1] : "127.0.0.1";

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
    30, 10, 5, 1.0, 1.0, 0.0, 1.0, -0.2, 0.2, 0.7, 0.18, 2,
    // Parametry dla obiektu (model wewnętrzny)
    0.8351, 0.2713, 2,
    // Parametry dla symulacji
    100, 1.0, "wyniki_dmc_B.csv");
    
    std::cout << "Scenariusz B zakończony." << std::endl << std::endl;

    // === SCENARIUSZ C: Zewnętrzny obiekt MATLAB połączony z klientem C++ przez TCP ===
    std::cout << "Scenariusz C: Model zewnętrzny przez TCP." << std::endl;

    try {
    wariant(30, 10, 5, 1.0, 1.0, 0.0, 1.0, -0.2, 0.2,
    100, 1.0, "wyniki_dmc_C.csv", adres_pc);
    std::cout << "Scenariusz C zakonczony." << std::endl << std::endl;
    }
    catch (const std::exception& e) 
    {
    std::cerr << "Scenariusz C nie powiodl sie: " << e.what() << std::endl << std::endl;
    }
}