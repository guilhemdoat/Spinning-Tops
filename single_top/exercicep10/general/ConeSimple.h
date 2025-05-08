#pragma once
#include "Toupie.h"
#include<iostream>
#include "constante.h"

class ConeSimple: public Toupie {  // On défini ici CoSimple, sous classe de toupie
private :
  double m_vol; //masse volumique
  double L; //hauteur
  double r_base; //rayon de la base

public :

//constructeur
  ConeSimple(Vecteur P, Vecteur P_point, double m, double l, double r);

// accesseurs
  double get_m_vol() const;

  double get_L() const override;

  double get_r_base() const override;

//méthode diverses
  virtual std::ostream& affiche(std::ostream& sortie) const override; //redéfinition de affiche de Toupie

  virtual void operator=(ConeSimple& autre);// nouvel operateur = prenant en compte le modulo 2pi

  Vecteur f(double& t) override; //redefintion de la fonction f de toupie

};
