#pragma once
#include "Support.h"
#include "constante.h"
#include<iostream>

class Dessinable { //classe abstraite
  protected :
    SupportADessin* Supp; //support a travers lequel le dessinable sera dessiné
  public:
    //constructeurs, destructeurs
    Dessinable();
    Dessinable(SupportADessin* s);
    ~Dessinable();



    //methodes diverses
    virtual void dessine() = 0;
    virtual void evolue(double dt, double t_debut, size_t indice_toupie, size_t indice_integ) = 0; //fait evoluer le dessinable d'un pas de temps



};





