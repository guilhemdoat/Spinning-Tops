
#pragma once

#include <iostream>
#include "Vecteur.h"
//#include "Dessinable.h"
//#include "Support.h"




class Toupie {
protected:
  Vecteur P; //(psi, theta, phi )
  Vecteur P_point;

public:
  //Accesseurs----------------------------------------
  Vecteur get_P();
  Vecteur get_P_point();
  void set_P(Vecteur const& p);
  void set_P_point(Vecteur const& p_point);
//------------------------------------------------------

// Constructeurs-------------------------------------
  Toupie();


  Toupie(Toupie const& autre);

  Toupie(Vecteur P, Vecteur P_point);

  Toupie(double psi, double theta, double phi, double psip, double thetap, double phip );

//Destructeur----------------------------------------
  ~Toupie();
//----------------------------------------------------
  virtual std::ostream& affiche(std::ostream& sortie) const;
  std::ostream& affiche_court(std::ostream& sortie) const;

  virtual void operator=(Toupie const& autre);


  virtual Vecteur f(double& t) = 0;

  virtual double get_L() const = 0;
  virtual double get_r_base() const  = 0;

  Vecteur trouve_axe(); // trouve l'axe de la toupie




};

std::ostream& operator<<(std::ostream& sortie, Toupie& T);










