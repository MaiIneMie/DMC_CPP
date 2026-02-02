#include "Offline.h"

// Konstruktor 
Offline::Offline(const Parametry& param)
{
    // Obliczenie M
    oblicz_M(param.s, param.N, param.Nu);

    // Obliczenie Mp
    oblicz_Mp(param.s, param.N, param.D);

    // Obliczenie K
    oblicz_K(param.N, param.Nu, param.alpha, param.beta);

}

void Offline::oblicz_M(const Eigen::VectorXd& s, int N, int Nu)
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

void Offline::oblicz_Mp(const Eigen::VectorXd& s, int N, int D)
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

void Offline::oblicz_K(int N, int Nu, double alpha, double beta)
{
    // Macierze wag (Identity - macierze jednostkowe)
    Eigen::MatrixXd Psi = alpha * Eigen::MatrixXd::Identity(N, N);
    Eigen::MatrixXd Lambda = beta * Eigen::MatrixXd::Identity(Nu, Nu);

    // Obliczenie K = (M^T * Psi * M + Lambda)^(-1) * M^T
    K = (M.transpose() * Psi * M + Lambda).inverse() * M.transpose();

}