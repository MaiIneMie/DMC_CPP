#ifndef STAN_H
#define STAN_H

#include <Eigen/Dense>

class Stan {
public:
    double y_k;    // obecne wyjście
    double u_k;    // obecne sterowanie
    Eigen::VectorXd v;  // historia przyrostów (długość D-1)
    
    // Konstruktor
    Stan(int D) 
    : y_k(0.0), u_k(0.0) 
    {
    v = Eigen::VectorXd::Zero(D - 1);
    }
};

#endif