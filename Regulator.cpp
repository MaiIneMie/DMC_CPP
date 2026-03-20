#include "Regulator.h"

// Konstruktor
Regulator::Regulator(int d, int n, int nu, double a, double b, double u_mi, double u_ma, double dv_mi, double dv_ma, double a_w, double b_w, int d_w)
: D(d), N(n), Nu(nu), alpha(a), beta(b), u_min(u_mi), u_max(u_ma), dv_min(dv_mi), dv_max(dv_ma)
{
    mod_wew = ObiektSymulowany(a_w, b_w, d_w);
    v = Eigen::VectorXd::Zero(D - 1);
    s = generuj_s(D);
    oblicz_macierze();
}

Regulator::Regulator(int d, int n, int nu, double a, double b, double u_mi, double u_ma, double dv_mi, double dv_ma, Eigen::VectorXd s)
: D(d), N(n), Nu(nu), alpha(a), beta(b), u_min(u_mi), u_max(u_ma), dv_min(dv_mi), dv_max(dv_ma), s(s)
{
    v = Eigen::VectorXd::Zero(D - 1);
    oblicz_macierze();
}
    


// Funkcja generująca odpowiedź skokową
Eigen::VectorXd Regulator::generuj_s(int D)
{
    // Deklaracja wektora wypełnionego wartościami odpowiedzi skokowej (rozmiar D)
    Eigen::VectorXd s(D);

    // Symulacja działania obiektu na wywołanie wartośći skokowej 1
    for (int k = 0; k < D; k++)
    {
        s(k) = mod_wew->krok_online(1.0);
    }

    // Zwrot wektora odpowiedzi skokowej
    return s;
}

void Regulator::oblicz_M()
{
    // Dostosowanie wymiarów macierzy (N wierszy, Nu kolumn)
    M.resize(N,Nu);

    // Pętla wypełniająca macierz (j zer na początku każdej kolumny a reszta s)
    for (int j = 0; j < Nu; j++)
    {
        for (int i = 0; i < N; i++)
        {
            // Jeśli indeks wiersza jest mniejszy od indeksu kolumny
            if (i < j)
            {
                // Wypełnij miejsce zerem
                M(i,j) = 0.0;
            }
            else
            {
                M(i,j) = s(i-j);
            }
        }
    }
}

void Regulator::oblicz_Mp()
{
    // Dostosowanie wymiarów macierzy (N wierszy i D-1 kolumn)
    Mp.resize(N, D - 1);
    for (int i = 0; i < N; i++)
    {
        for( int j = 0; j < D -1; j++)
        {
            // Obliczenie indeksu łączonego tak aby nie wyjść poza zakres s (D-1)
            int indeks = ( (i + j + 1) < D) ? (i + j + 1) :  (D-1);
            Mp(i,j) = s(indeks) - s(j);
        }
    }
}

void Regulator::oblicz_K()
{
    // Macierze wag (Identity - macierze jednostkowe)
    Eigen::MatrixXd Psi = alpha * Eigen::MatrixXd::Identity(N, N);
    Eigen::MatrixXd Lambda = beta * Eigen::MatrixXd::Identity(Nu, Nu);

    // Obliczenie K = (M^T * Psi * M + Lambda)^(-1) * M^T
    // 1. Obliczenie A (A = M^T · Psi · M + Lambda)
    // 2. Obliczenie B (B = M^T · Psi)
    // 3. Rozłożenie A na trzy macierze - L (trójkątna dolna), D (diagonalna), L^T
    // 4. Rozwiązanie A · K = B
    K = (M.transpose() * Psi * M + Lambda).ldlt().solve(M.transpose() * Psi);
    
}

void Regulator::oblicz_macierze() // Macierze
{
    oblicz_M();
    oblicz_Mp();
    oblicz_K();
} 

// Funkcja utrzymująca daną wartość w odpowiednim zakresie
double Regulator::ogranicz(double wartosc, double min, double max)
{
    if (wartosc < min) return min;
    if (wartosc > max) return max;
    return wartosc;
}

void Regulator::krok_regulacji(double y_k, double yzad_k)
{
    // Wektor wartości zadanych Yzad (N elementów = N wierszy)
    Eigen::VectorXd Yzad = Eigen::VectorXd::Constant(N, yzad_k);

    // Wektor wolnej odpowiedzi z przeszłością Y0 = y_k + Mp*v
    Eigen::VectorXd Y0 = Eigen::VectorXd::Constant(N, y_k) + Mp * v;

    // Wektor błędu E = Yzad - Y0
    Eigen::VectorXd E = Yzad - Y0;

    // Wektor przyrostów sterowania v = K * E
    Eigen::VectorXd przyrosty = K * E;

    // Pobranie pierwszego elementu z tablicy przyrostów
    double v_k = przyrosty(0);

    // Ograniczenie przyrostu
    v_k = ogranicz(v_k, dv_min, dv_max);

    // Obliczenie nowego sterowania
    u_k = u_k + v_k;

    // Ograniczenie sterowanie
    u_k = ogranicz(u_k, u_min, u_max);

    // Aktualizacja historii przyrostów
    for (int i = v.size() - 1; i > 0; i--) // Zaczynając od końca w dół
    {
        v(i) = v(i - 1); // Przypisanie elementowi wartości o jeden mniejszej (28 skopiowany z 27 itd)
    }

    v(0) = v_k; // Element pierwszy to najnowszy przyrost

    this->y_k = y_k;
    this->u_k = u_k;
} 

