/*
================================================================================================================

Integrateur.cc

================================================================================================================
*/


#include "Integrateur.h"
#include "Toupie.h"

using namespace std;


  //constructeurs, destructeur
  Integrateur::Integrateur(double d, Toupie* t) : dt(d) {
    toupie = t;
  }

  Integrateur::Integrateur() {dt = 0.01;}
  Integrateur::~Integrateur() {}


 //accesseurs, manipulateurs
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
















