#pragma once

#include "Integrateur.h"
#include "Toupie.h"


class IntegrateurEulerCromer: public Integrateur { //IntégrateurEulerCromer est un Intégrateur
public :
  virtual Toupie* integre(double t) override; //redéfinition de integre de Intégrateur
  
  //constructeurs, destructeurs
  IntegrateurEulerCromer();
  ~IntegrateurEulerCromer();
  IntegrateurEulerCromer(double dt, Toupie* t);


};
