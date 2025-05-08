#include <iostream>
#include "Vecteur.h"
#include <string>
#include <vector>

#include "Matrice33.h"

using namespace std;


//private-----------------------------------------------
  Vecteur v1; // ce sont des vecteurs colonne(s)
  Vecteur v2;
  Vecteur v3;
//------------------------------------------------------


//public-----------------------------------------------
 //Constructeurs---------------------------------------
  Matrice33::Matrice33(Vecteur vect1, Vecteur vect2, Vecteur vect3) {
    v1 = vect1;
    v2 = vect2;
    v3 = vect3;
  }

  Matrice33::Matrice33() {
    this->v1.set_coord(0, 1);
    this->v2.set_coord(1, 1);
    this->v3.set_coord(2, 1);
  }

  Matrice33::Matrice33(double a, double b, double c) {
    v1.set_coord(0, a);
    v2.set_coord(1, b);
    v3.set_coord(2, c);
  }
 //-----------------------------------------------------

 //Accesseurs/Manipulateurs-----------------------------

  double Matrice33::get_coef(int ligne, int colonne) const {
    switch(colonne) {
      case 1 : return v1.get_coord(ligne-1); // on commence les indices à 1
      case 2 : return v2.get_coord(ligne-1);
      case 3 : return v3.get_coord(ligne-1);
      default : throw string("Erreur dans l'appel a la colonne de la matrice.");
    }
  }

  Vecteur Matrice33::get_colonne(int i) const{
    switch(i) {
      case 1 : return v1;
      case 2 : return v2;
      case 3 : return v3;
      default : return v1; //ne devrait jamais arriver
    }

  }

    void Matrice33::set_colonne(int i, Vecteur const& v) {
      if(v.get_vect().size() == 3) {
        switch(i) {
          case 1 : v1 = v;
          case 2 : v2 = v;
          case 3 : v3 = v;
          
        }
      }

    }

    void Matrice33::set_coef(int ligne, int colonne, double valeur) {
       switch(colonne) {
        case 1 : v1.set_coord(ligne - 1, valeur); // on enlève à al valeur en arguement pour pouvoir utiliser la notation standard de matrices (i,j) avec i,j >= 1
        case 2 : v2.set_coord(ligne - 1, valeur);
        case 3 : v3.set_coord(ligne - 1, valeur);
      }
    }

// Méthodes de calcul ------------------------------------------------------------------------------------------
    double Matrice33::det() const { // calcul du déterminant
      double d = v1.get_coord(0)*(v2.get_coord(1)*v3.get_coord(2)-v3.get_coord(1)*v2.get_coord(2))  -  v2.get_coord(0)*(v1.get_coord(1)*v3.get_coord(2)-v3.get_coord(1)*v1.get_coord(2)) + v3.get_coord(0)*(v1.get_coord(1)*v2.get_coord(2)-v2.get_coord(1)*v1.get_coord(2));

      if(compare_(d, 0, 1e-5)) return 0.;
      return d;
      //car si det(M) = 0 en realite le calcul donne souvent un nombre tres petit mais non nul
  }

  Matrice33  Matrice33::inv() const { //calcul de l'inverse

    double d(det());
    if(compare_(d, 0, 1e-5)) { // on verifie que le det ne sois pas "nul"
      Matrice33 m(0,0,0);
      return m;
    }

    Vecteur vect1({v2.get_coord(1)*v3.get_coord(2) - v3.get_coord(1)*v2.get_coord(2),
    v3.get_coord(1)*v1.get_coord(2) - v1.get_coord(1)*v3.get_coord(2), v1.get_coord(1)*v2.get_coord(2) - v2.get_coord(1)*v1.get_coord(2)});

    Vecteur vect2({v3.get_coord(0)*v2.get_coord(2) - v2.get_coord(0)*v3.get_coord(2) , v1.get_coord(0)*v3.get_coord(2) - v3.get_coord(0)*v1.get_coord(2) ,  v2.get_coord(0)*v1.get_coord(2) - v1.get_coord(0)*v2.get_coord(2)});

    Vecteur vect3({v2.get_coord(0)*v3.get_coord(1) - v3.get_coord(0)*v2.get_coord(1) , v3.get_coord(0)*v1.get_coord(1) - v1.get_coord(0)*v3.get_coord(1) , v1.get_coord(0)*v2.get_coord(1) - v2.get_coord(0)*v1.get_coord(1)});


    Matrice33 m(vect1, vect2, vect3);
    m = (1/d)*m;
    return m;
  }
  //---------------------------------------------------
  //Opérateurs------------------------------------------
  const Matrice33 Matrice33::operator+(Matrice33 const& autre) const { //redefinition de l'addition
    Matrice33 resultat(0,0,0);
    for(int i(1); i <= 3; ++i) {
      resultat.set_colonne(i, this->get_colonne(i)+autre.get_colonne(i));
    }
    return resultat;

  }

  Matrice33 Matrice33::M_oppose() const{ // fonction oppose dans le meme esprit que celle pour les vecteurs
    Matrice33 opp(0,0,0);
    opp.v1 = this->v1.oppose();
    opp.v2 =  this->v2.oppose();
    opp.v3 =  this->v3.oppose();
    return opp;
  }

    Matrice33 Matrice33::operator-(Matrice33 autre) const { //redefinition de la soustraction
        return *this + autre.M_oppose();
  }

  Matrice33 Matrice33::transp(){ // On fait la transposée classique en allant chercher les coefs aux bons endroits.
    Matrice33 T(0,0,0);
    for(int i(1); i<=3; ++i){
      Vecteur _v(this->get_coef(i,1), this->get_coef(i,2), this->get_coef(i,3));
      T.set_colonne(i, _v);
     }
     return T;
  }



  const Matrice33 Matrice33::operator*(Matrice33 const& autre) const { //produit matriciel
    Matrice33 resultat;
    for(int i(1); i<=3; ++i){
      for(int j(1) ; j <=3 ; ++j) {
        double coef(0);
        for(int k(1) ; k<= 3 ; ++k) {
          coef += get_coef(i, k)*autre.get_coef(k, j);
        }
        resultat.set_coef(i, j, coef);
      }
    }
    return resultat;
  }

  const Vecteur Matrice33::operator*(Vecteur const& autre) {//multiplication a droite par un vecteur
    Vecteur resultat;
    Matrice33 T(*this);
    T.transp();

    for(int i(1) ; i <= 3 ; ++i) {
      resultat.set_coord(i-1, T.get_colonne(i)*autre);
    }
    return resultat;
  }

  ostream& Matrice33::affiche(ostream& sortie) const{ //fonction d'affichage
    Matrice33 tmp = *this;
    tmp = tmp.transp();
    for(int i(1); i<=3; ++i){

      sortie << tmp.get_colonne(i);
      sortie << endl;
    }
    sortie  << endl;
    return sortie;

  }
//------------------------------------------------------
//fin de classe


ostream& operator<<(ostream& sortie, Matrice33 m){
  return m.affiche(sortie);
}

const Matrice33 operator*(double const& lambda, Matrice33 const& m) {// multiplication a gauche par un scalaire en utilisant la multiplication par un scalaire des vecteurs
//comme c'est une multiplication a gauche on doit faire une methode externe
    Matrice33 resultat(0,0,0);
    for(int i(1); i <= 3; ++i) {
      resultat.set_colonne(i, m.get_colonne(i)*lambda);
    }
    return resultat;
  }


