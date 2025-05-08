/*
================================================================================================================

Integrateur.cc

================================================================================================================
*/


#include "Integrateur.h"
#include "Toupie.h"

using namespace std;


  //constructeur----------------------------------------
  Integrateur::Integrateur(double d, Toupie* t) : dt(d) {
    toupie = t;
  }

  Integrateur::Integrateur() {}

  //Destructeur------------------------------------------
  Integrateur::~Integrateur() {}


 //accesseurs--------------------------------------------
 double Integrateur::get_dt() const {
   return dt;
  }

 Toupie* Integrateur::get_toupie() const {
   return toupie;

  }

  void Integrateur::set_dt (double d){
    dt=d;
  }


  void Integrateur::set_toupie(Toupie* toup) {
    toupie = toup;
  }














