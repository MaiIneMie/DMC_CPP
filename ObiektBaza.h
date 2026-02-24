#ifndef OBIEKTBAZA_H
#define OBIEKTBAZA_H

class ObiektBaza {
public:
    virtual double krok_online(double u_k) = 0; // Deklaracja
    virtual ~ObiektBaza() {}  // Destruktor
};

#endif