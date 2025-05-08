#pragma once
#include <vector>
#include <iostream>//pour operator<<
#include "Vecteur.h"


class Matrice33{
private:
  Vecteur v1; // ce sont des vecteurs colonne(s)
  Vecteur v2;
  Vecteur v3;

public:

// Constructeurs --------------------------------------
  Matrice33(Vecteur v1, Vecteur v2, Vecteur v3);

  Matrice33();

  Matrice33(double a, double b, double c);

//------------------------------------------------------


//Accesseurs/Manipulateurs------------------------------
  double get_coef(int ligne, int colonne) const;

  Vecteur get_colonne(int i) const;

  void set_colonne(int i, Vecteur const& v);

  void set_coef(int ligne, int colonne, double valeur);

  double det() const;

  Matrice33  inv() const;

//------------------------------------------------------

//Opérateurs--------------------------------------------
  const Matrice33 operator+(Matrice33 const& autre) const;

  Matrice33 M_oppose() const;

    Matrice33 operator-(Matrice33 autre) const;

  Matrice33 transp();

  const Matrice33 operator*(Matrice33 const& autre) const; //produit matriciel

  const Vecteur operator*(Vecteur const& autre); //multiplication a droite par un vecteur

  std::ostream& affiche(std::ostream& sortie) const; // utilise par operator<<
//------------------------------------------------------
};
std::ostream& operator<<(std::ostream& sortie, Matrice33 m);
//operateur de sortie : il est externe mais nous avons fait ainsi.

const Matrice33 operator*(double const& lambda, Matrice33 const& m); // externe pour pouvoir faire la multiplication a gauche
