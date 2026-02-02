#ifndef OGRANICZENIA_H
#define OGRANICZENIA_H

class Ograniczenia {
public:
    double u_min;
    double u_max;
    double dv_min;
    double dv_max;
    
    // Konstruktor
        Ograniczenia(double u_min, double u_max, double dv_min, double dv_max)
        : u_min(u_min), u_max(u_max), dv_min(dv_min), dv_max(dv_max) {}
};

#endif