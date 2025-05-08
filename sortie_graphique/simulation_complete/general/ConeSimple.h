#pragma once
#include "Toupie.h"
#include<iostream>
#include "constante.h"
#include "Matrice33.h"

class ConeSimple: public Toupie {
protected:
  //================ attributs ===================================================
  double m_vol; //masse volumique
  double L;     //longueur
  double r_base;//rayon de la base

  Vecteur LA_moment, L_moment, omega;
  double IA1, IA3, I1, I3;  // IA = diag(IA1, IA1, IA3) ; I = diag(I1, I1, I3)
  Matrice33 IA, I; //Matrices d'inertie
  Matrice33 matrice_passage; // matrice de passage du referentiel RG au referentiel RO
  double masse;

  double produit_mixte; //a.(omega x L) : doit etre egal a 0 si la simulation fonctionne car a, omega et L sont coplanaires
  double energie;
  double LA_k, LA_a; // projection du moment cinetique en A sur le vecteur unite k (axe Oz) et a (axe principal de la toupie)


  //================ methodes protected ==================================================


    //seule la methode calcule() sera accessible pour un utilisateur.
    void calcule_invariants();

    double calcule_produit_mixte() const; //voir description dans la declaration des attributs
    double calcule_energie() const;
    double calcule_LA_k() const;
    double calcule_LA_a() const;

    void calcule_autres(); //pour calculer toutes les autres valeurs qui ne seront pas directement affichees


public :

  //constructeurs
  ConeSimple(Vecteur P, Vecteur P_point, double m, double l, double r);
  ConeSimple();

  //accesseurs
  double get_m_vol() const;
  double get_L() const override;
  double get_r_base() const override;


  //========================= methodes diverses ===================================
  void calcule() override; //methode generale qui calcule toutes les valeurs caracteristiques

  virtual std::ostream& affiche(std::ostream& sortie) const override;
  virtual std::ostream& affiche_invariants(std::ostream& sortie) const override;

  //redefinition des operateurs =
  virtual void operator=(ConeSimple& autre);
  virtual void operator=(Toupie& autre) override;

  Vecteur f(double t, Vecteur P, Vecteur P_point) override;

};
