#ifndef OBIEKTBAZA_H
#define OBIEKTBAZA_H

class ObiektBaza {
public:
    virtual double krok_online(double u_k) = 0; // Deklaracja
    virtual void reset() = 0;
    virtual double get_stan() const = 0;
    virtual ~ObiektBaza() {}  // Destruktor
};

#endif