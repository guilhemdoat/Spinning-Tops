#include "ConeSimple.h"
#include "Toupie.h"
#include <iostream>
#include <cmath>

using namespace std;

//Constructeur-------------------------------------------------
  ConeSimple::ConeSimple(Vecteur P, Vecteur P_point, double m, double l, double r) : Toupie(P, P_point), m_vol(m), L(l), r_base(r) {};

//Accesseurs---------------------------------------------------
  double ConeSimple::get_m_vol() const {
    return m_vol;
  }

  double ConeSimple::get_L() const {return L;}

  double ConeSimple::get_r_base() const { return r_base;}

  void ConeSimple::operator=(ConeSimple& toupie) { // redéfinition de l'opérateur = afin de prendre en compte le modulo 2pi
    this->P = toupie.get_P().mod_2pi();
    this->P_point = toupie.get_P_point();
  }


  //pour l'operator<<
  ostream& ConeSimple::affiche(ostream& sortie) const {
    Toupie::affiche(sortie);

    sortie << "masse volumique : " << this->m_vol << endl;

    sortie << "rayon de la base : " << this->get_r_base() << endl;

    sortie << "Hauteur : " << this->get_L() << endl;




    return sortie;
  }




   Vecteur ConeSimple::f(double& t) { // définition de la fonction f telle que montré dans le complément mathématique
     //dans l'ordre : psi, theta, phi
     double d = L*3/4 ;//d = ||AG|| avec G le centre de masse, A le point de contact
    double m = M_PI*m_vol*r_base*r_base*L/3;
    double I3 = 3*m*r_base*r_base/10;
    double Ia1 = 3*m*(r_base*r_base/20 + L*L/5);

    //dans notre exemple, theta = pi/6, psi=phi = 0 ; 
    //theta_P = psi_P = 0 ; phi_P = 60 rad/sec
    
    double psi = P.get_coord(0);
    double theta = P.get_coord(1);
    double phi = P.get_coord(2);
    double psi_P = P_point.get_coord(0);
    double theta_P = P_point.get_coord(1);
    double phi_P = P_point.get_coord(2);
    

    double psi_PP = ((I3-2*Ia1)*psi_P*cos(theta)+I3*phi_P)*theta_P/(Ia1*sin(theta));

    double theta_PP = (m*g_scalaire*d*sin(theta) + psi_P*sin(theta)*((Ia1-I3)*psi_P*cos(theta)-I3*phi_P))/Ia1;

    double phi_PP = ((Ia1-(I3-Ia1)*cos(theta)*cos(theta))*psi_P-I3*phi_P*cos(theta))*theta_P/(Ia1*sin(theta));

    Vecteur v(psi_PP, theta_PP, phi_PP);
    return v;
  }


