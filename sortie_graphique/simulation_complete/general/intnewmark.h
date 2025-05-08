#pragma once
#include "Integrateur.h"
#include "Toupie.h"
#include "Vecteur.h"



class IntegrateurNewmark: public Integrateur
{
private:
    //attributs pour l'integration
    double eps;
    Vecteur q, r, s;
public:
    //methode qui integre la toupie du pas de temps dt
    virtual Toupie* integre(double t) override;

    //constructeurs, destructeur
    IntegrateurNewmark();
    ~IntegrateurNewmark();
    IntegrateurNewmark(double dt, Toupie* t, double espilon=1e-5);
};

