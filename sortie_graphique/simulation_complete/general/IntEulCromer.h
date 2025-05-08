#pragma once
#include "Integrateur.h"
#include "Toupie.h"


class IntegrateurEulerCromer: public Integrateur {
public :
  //methode qui integre la toupie du pas de temps dt
  virtual Toupie* integre(double t) override;
  
  //constructeurs, destructeurs
  IntegrateurEulerCromer();
  ~IntegrateurEulerCromer();
  IntegrateurEulerCromer(double dt, Toupie* t);


};
