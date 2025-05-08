#include "Toupie.h"
#include "IntEulCromer.h"

using namespace std;



Toupie* IntegrateurEulerCromer::integre(double t) { // fonction integre qui set P et P_point selon les équations différentielles données dans le complément mathématique
  
  toupie->set_P_point(this->toupie->get_P_point() + this->toupie->f(t)*this->dt);
  

  toupie->set_P(this->toupie->get_P() + toupie->get_P_point()*this->dt);

  return toupie;

}




//Constructeurs
IntegrateurEulerCromer::IntegrateurEulerCromer() {};
IntegrateurEulerCromer::IntegrateurEulerCromer(double dt, Toupie* t) : Integrateur(dt, t) {};

//Destructeur
IntegrateurEulerCromer:: ~IntegrateurEulerCromer() {};

