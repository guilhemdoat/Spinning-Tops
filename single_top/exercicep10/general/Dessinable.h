#pragma once
#include "Support.h"
#include<iostream>

class Dessinable {
  protected :
    SupportADessin* Supp;
  public:
// constructeurs
    Dessinable();

    Dessinable(SupportADessin* s);

// Destructeur
    ~Dessinable();

//Méthode diverses
    virtual void dessine() = 0;


    virtual void evolue(double dt, double t_debut) = 0;



};





