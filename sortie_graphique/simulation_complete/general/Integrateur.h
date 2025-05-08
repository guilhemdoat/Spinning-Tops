#pragma once
#include "Toupie.h"
#include "Vecteur.h"



class Integrateur { //classe abstraite
protected :
  double dt; //pas de temps
  Toupie* toupie; //pointeur vers la toupie a integrer (pointeur car Toupie est une classe abstraite)
public :
  //constructeurs, destructeur
  Integrateur(double d, Toupie* t);
  Integrateur();
  virtual ~Integrateur();

  //accesseurs, manipulateurs :
  double get_dt() const;
  Toupie* get_toupie() const;
  void  set_dt(double d);
  void set_toupie(Toupie* toup);

  //methode qui integre la toupie du pas de temps dt
  virtual Toupie* integre(double t_debut) = 0; //ici elle est virtuelle pure
};













