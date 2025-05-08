#include "Toupie.h"
#include "IntEulCromer.h"

using namespace std;



Toupie* IntegrateurEulerCromer::integre(double t) {
  
  toupie->set_P_point(this->toupie->get_P_point() + this->toupie->f(t, toupie->get_P(), toupie->get_P_point())*this->dt);
  
  toupie->set_P(this->toupie->get_P() + toupie->get_P_point()*this->dt);



  return toupie;

}




//constructeurs, destructeur
IntegrateurEulerCromer::IntegrateurEulerCromer() {};
IntegrateurEulerCromer:: ~IntegrateurEulerCromer() {};
IntegrateurEulerCromer::IntegrateurEulerCromer(double dt, Toupie* t) : Integrateur(dt, t) {};
