#include <iostream>
#include <vector>
#include <cmath>

#include "Vecteur.h"

using namespace std;











  //utile tres souvent
bool compare_(double x, double y, double precision) {return abs(x-y) < precision;} //méthode de comparaison à une certaine précision près


//public


//------------------------------------------
//constructeurs

    Vecteur::Vecteur() {
        for(int i(0) ; i < 3 ; ++i) { //pour les matrices 3x3
            v.push_back(0);
        }
        compteur++;
    }

    Vecteur::Vecteur(int const& dim) { //pour les matrices, on utilise que des vecteurs de dim = 3
        for(int i(0); i < dim; ++i){
          v.push_back(0);
        }
        compteur++;
    }


  Vecteur::Vecteur(initializer_list<double> const& liste) {
    for(auto i : liste) {
      v.push_back(i);
    }
    compteur++;
  }


  Vecteur::Vecteur(double x, double y, double z) {
    v.push_back(x);
    v.push_back(y);
    v.push_back(z);
    compteur++;
  }

  Vecteur::Vecteur(Vecteur const& autre) : v(autre.get_vect()) {compteur++;}


//----------------------------------------


//--------------------------------------
//Accesseurs/Manipulateurs

vector<double> Vecteur::get_vect() const {
    return this->v;
  }

void Vecteur::augmente(const double& valeur) {
    this->v.push_back(valeur);
  }

void Vecteur::set_coord(int pos, double valeur) {
    this->v[pos] = valeur;
  }

double Vecteur::get_coord(int pos) const{
    return this->v[pos];
  }




void Vecteur::trouve_valeurs(size_t& taille_max, size_t& taille_min, vector<double>& grand, vector<double>& petit, Vecteur autre) const {
  //fonction qui nous permet d'implementer l'addition / produit scalaire de deux vecteurs de dim differentes
    if(this->v.size() >= autre.get_vect().size()){
    taille_max = this->v.size();
    taille_min = autre.get_vect().size();
    grand = this->v;
    petit = autre.get_vect();


  } else {
    taille_max = autre.get_vect().size();
    taille_min = this->v.size();
    grand = autre.get_vect();
    petit = this->v;
  }

  }


Vecteur Vecteur::oppose() const{ // trouve l'opposé du vecteur
  Vecteur opp;
  for( size_t i(0); i < this->v.size() ; ++i){
    opp.set_coord(i, -(this->v[i]));
  }
  return opp;
}



double Vecteur::norme2() const { //calcul la norme au carré
  double resultat(0.0);
  for(auto i : this->v) {
    resultat += i*i;
  }
  return resultat;
}

double Vecteur::norme() const { // calcul la norme euclidienne
  return sqrt(norme2());
}

Vecteur Vecteur::mod_2pi() const {
    Vecteur sortie(*this);

    for(size_t i(0) ; i < sortie.get_vect().size() ; ++i) {
        sortie.set_coord(i, fmod(sortie.get_coord(i), 2*M_PI));
    }
    return sortie;
}

//------------------------------


//------------------------------------------
//surcharge d'operateurs


ostream& Vecteur::affiche(ostream& sortie) const {
    for(size_t i(0); i < this->v.size(); ++i){
        sortie << this->v[i] << " ";
      }
      return sortie;
  }

ostream& operator<<(ostream& sortie, Vecteur v)  {
      return v.affiche(sortie);
}

const bool Vecteur::operator==(Vecteur const& vc) const {
    if(vc.get_vect().size() == this->v.size()) {
      for(size_t i(0) ; i < v.size() ; ++i) {
        if(!compare_(vc.get_vect()[i], this->v[i], 1e-10)) return false;
      }
      return true;
    }
    return false;
  }

const bool Vecteur::operator!=(Vecteur const& vc) const  {
    return !(*this == vc);
  }

  const Vecteur Vecteur::operator+(Vecteur const& autre) const{ //surcharge de +, capable de gérer une addition de vecteurs de dimensions diférentes, ce qui ne devrait pas arriver
    Vecteur result(autre.get_vect().size());
    size_t taille_max;
    size_t taille_min;
    vector<double> grand, petit;

    trouve_valeurs(taille_max, taille_min, grand, petit, autre);


    for(size_t i(0); i < taille_min; ++i){
      result.set_coord(i, grand[i]+petit[i]);
    }

    for(size_t i(taille_min); i < taille_max; ++i){ // on ajoute juste au vecteurs final les coordonnées "en trop" du plus grand vecteur
      result.set_coord(i, grand[i]);
    }


  return result;
}

const Vecteur Vecteur::operator-(Vecteur const& autre) const { //surcharge de -
  return *this + autre.oppose();
}

 const Vecteur Vecteur::operator*(double lambda) const{ // multiplication par un scalaire
  Vecteur result(v.size());
  for(size_t i(0); i < this->v.size() ; ++i){
    result.set_coord(i, lambda*this->v[i]);
  }
  return result;
}

const double Vecteur::operator*(Vecteur autre) const{ // produit scalaire, aussi capable de gérer des veceteurs de tailles différentes
 double result(0.0);
  size_t taille_max;
  size_t taille_min;
  vector<double> grand, petit;

  trouve_valeurs(taille_max, taille_min, grand, petit, autre);

  for(size_t i(0); i < taille_min; ++i){
    result += (grand[i]*petit[i]);
  }

  for(size_t i(taille_min); i < taille_max; ++i){
    result += grand[i];
  }

  return result;
}






const Vecteur Vecteur::operator^(Vecteur autre) const { // produit vectoriel
  Vecteur resultat(3);
  if(autre.get_vect().size() != 3 or this->v.size() != 3)throw string("Erreur dans le produit vectoriel : la dimension de l'un des vecteurs n'est pas de 3.");

  resultat.set_coord(0, this->v[1]*autre.get_vect()[2]-this->v[2]*autre.get_vect()[1]);
  resultat.set_coord(1, this->v[2]*autre.get_vect()[0]-this->v[0]*autre.get_vect()[2]);
  resultat.set_coord(2, this->v[0]*autre.get_vect()[1]-this->v[1]*autre.get_vect()[0]);

  return resultat;
}

const Vecteur Vecteur::operator~() const { //méthode de normalisation
  Vecteur out(*this);
  out *= 1/out.norme();
  return out;
}

// Surcharge des (opérations)= ----------------------------------
void Vecteur::operator+=(Vecteur const& autre) {
  *this = *this + autre;
}

const void Vecteur::operator-=(Vecteur const& autre) {
  *this = *this + autre;
}

 const void Vecteur::operator*=(Vecteur const& autre) {
    *this = (*this)*autre;
  }

const void Vecteur::operator*=(double lambda){
  *this = (*this)*lambda;
}


  const void Vecteur::operator^=(Vecteur const& autre) {
    *this = (*this)^autre;
  }



//---------------------------------------------
//fin de classe
