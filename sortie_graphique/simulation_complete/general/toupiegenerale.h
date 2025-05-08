#pragma once
#include "ConeSimple.h"

class Vecteur; //si on met #include "Vecteur.h" on a une erreur "undefined reference to vtable for toupiegenerale"

class ToupieGenerale: public ConeSimple
{
public:

    //constructeur
    ToupieGenerale(Vecteur P, Vecteur P_point, double m, double l, double r);

    //equation differentielle d'une toupie generale
    virtual Vecteur f(double t, Vecteur P, Vecteur P_point) override;

    std::ostream& affiche(std::ostream &sortie) const override;
};

