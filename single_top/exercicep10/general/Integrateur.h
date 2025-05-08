/*
================================================================================================================

Integrateur.h

================================================================================================================
*/



#pragma once
#include "Toupie.h"



class Integrateur {
protected :
  double dt;
  Toupie* toupie;
public :
  //comme notre integrateur doit retourner P(t+dt) et P_point(t+dt) on va les passer par reference


//constructeurs
  Integrateur(double d, Toupie* t);
  Integrateur();

//Destructeur
  ~Integrateur();

//accesseurs :
  double get_dt() const;
  Toupie* get_toupie() const;
  void  set_dt(double d);
  void set_toupie(Toupie* toup);

// Méthodes diverses
  virtual Toupie* integre(double t_debut) = 0;
};













