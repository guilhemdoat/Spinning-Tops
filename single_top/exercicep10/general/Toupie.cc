#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include "Vecteur.h"
#include "Toupie.h"
#include "Matrice33.h"


using namespace std;


//Accesseurs----------------------------------------
  Vecteur Toupie::get_P(){
    return P;
  }

  Vecteur Toupie::get_P_point() {
    return P_point;
  }

  void Toupie::set_P_point(Vecteur const& v) {
    this->P_point = v;
  }

  void Toupie::set_P(Vecteur const& v){
    this->P = v.mod_2pi();
  }
//------------------------------------------------------

// Constructeurs-------------------------------------
  Toupie::Toupie(){
    Vecteur tmp1; //parametre et vitesse en 3D nul
    P = tmp1;
    P_point = tmp1;

  }



  Toupie::Toupie(Toupie const& autre): P(autre.P), P_point(autre.P_point){}

  Toupie::Toupie(Vecteur P, Vecteur P_point): P(P), P_point(P_point){}

  Toupie::Toupie(double psi, double theta, double phi, double psip, double thetap, double phip ){
    this->P.set_coord(1,fmod(psi, 2*M_PI));
    this->P.set_coord(2,fmod(theta, 2*M_PI));
    this->P.set_coord(3,fmod(phi, 2*M_PI));

    this->P_point.set_coord(1,psip);
    this->P_point.set_coord(2,thetap);
    this->P_point.set_coord(3,phip);
  }
//Destructeur
  Toupie::~Toupie() {}

//----------------------------------------------------
   ostream& Toupie::affiche(ostream& sortie) const {
    for(size_t i(0) ; i < (P.get_vect()).size() ; ++i) {
      sortie << P.get_coord(i) << ", ";
    }
    sortie << " # parametre" << endl;

    for(size_t i(0) ; i < (P_point.get_vect()).size() ; ++i) {
      sortie << P_point.get_coord(i) << ", ";
    }
    sortie << " # vitesse" << endl;
    return sortie;

  }

  ostream& Toupie::affiche_court(ostream& sortie) const {
    sortie << "paramètre : " << P << ", derivee : " << P_point << endl;
    return sortie;
  }

   

  void Toupie::operator=(Toupie const& autre) {
    this->P_point = autre.P_point;
    this->P = autre.P;
  }


  Vecteur Toupie::trouve_axe(){      //trouve l'axe du cone à l'aide de la matrice de transition et d'une matrice de rotation

      double sin_psi(sin(this->get_P().get_coord(0))); // on récupère les coordonnées de P (les angles d'Euler de la toupie)
      double cos_psi(cos(this->get_P().get_coord(0)));
      double cos_theta(cos(this->get_P().get_coord(1)));
      double sin_theta(sin(this->get_P().get_coord(1)));

      Vecteur colonne1(cos_psi, -cos_theta*sin_psi, sin_theta*sin_psi); // création de la matrice de passage
      Vecteur colonne2(sin_psi, cos_psi*cos_theta, -sin_theta*cos_psi);
      Vecteur colonne3(0, sin_theta, cos_theta);



      colonne1.mod_2pi();
      colonne2.mod_2pi();
      colonne3.mod_2pi();



      Vecteur c1(cos_psi, -sin_psi, 0); // création de la matrice de rotation
      Vecteur c2(sin_psi, cos_psi, 0);
      Vecteur c3(0,0,1);

      c1.mod_2pi();
      c2.mod_2pi();
      c3.mod_2pi();

      Matrice33 m_rotation_psi(c1,c2,c3);

      Matrice33 matrice_passage(colonne1, colonne2, colonne3);

      Matrice33 m(m_rotation_psi*matrice_passage);

      Vecteur Axe_z(0.0,0.0,1.0);// L'axe "d'origine" est donc ici l'axe Z

      return m * Axe_z;
  }






ostream& operator<<(ostream& sortie, Toupie& T) {
  return T.affiche(sortie);
}





