#pragma once
#include "Integrateur.h"


class IntegrateurRungeKutta: public Integrateur
{
private:
    //attributs pour l'integration : nous avons decide de les mettre en attribut plutot que de
    //devoir les declarer a chaque integration
    Vecteur k1, k2, k3, k4, kp1, kp2, kp3, kp4;
public:
    //constructeur
    IntegrateurRungeKutta(double d, Toupie* t): Integrateur(d, t) {};
    IntegrateurRungeKutta() {};
    ~IntegrateurRungeKutta() {};

    //methode qui integre la toupie du pas de temps dt
    virtual Toupie* integre(double t_debut) override;
};

