#ifndef ONLINE_H
#define ONLINE_H

#include <Eigen/Dense>
#include "Stan.h"
#include "Parametry.h"
#include "Offline.h"
#include "Ograniczenia.h"

class Online {
public:
    // Jeden krok regulacji - modyfikuje stan
    void krok(Stan& stan, const Parametry& param, const Offline& off,
              const Ograniczenia& ogr, double y_k, double yzad_k);

private:
    // Pomocnicze funkcje prywatne
    double ogranicz(double wartosc, double min, double max);
};

#endif