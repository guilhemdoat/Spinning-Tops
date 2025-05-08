#pragma once
#include <iostream>
#include "Vecteur.h"
#include "Matrice33.h"




class Toupie { //classe abstraite
protected:
  Vecteur P; //(psi, theta, phi )
  Vecteur P_point; //(psip, thetap, phip)

public:
  //Accesseurs----------------------------------------
  Vecteur get_P();
  Vecteur get_P_point();
  void set_P(Vecteur const& p);
  void set_P_point(Vecteur const& p_point);
//------------------------------------------------------

// ======================= Constructeurs, destructeur ===============================
  Toupie();


  Toupie(Toupie const& autre);

  Toupie(Vecteur P, Vecteur P_point);

  Toupie(double psi, double theta, double phi, double psip, double thetap, double phip );

  virtual ~Toupie();
//========================= sortie et operateurs =====================
  virtual std::ostream& affiche(std::ostream& sortie) const;
  std::ostream& affiche_court(std::ostream& sortie) const;
  virtual std::ostream& affiche_invariants(std::ostream& sortie) const = 0;


  virtual void operator=(Toupie& autre);

  //====================== Methodes diverses =======================================
  virtual Vecteur f(double t, Vecteur P, Vecteur P_point) = 0;

  virtual void calcule() = 0;

  Matrice33 calcule_matrice_passage() const; // matrice de passage du referentiel RG au referentiel RO

  //ces deux methodes peuvent etre presentes ici car on a pas implemente toupie chinoise : si on l'avait fait, on
  //aurait du les enlever
  virtual double get_L() const = 0;
  virtual double get_r_base() const  = 0;

  Vecteur trouve_axe(); //retourne l'axe de rotation de la toupie




};

std::ostream& operator<<(std::ostream& sortie, Toupie& T);










