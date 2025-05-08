/*
================================================================================================================

Systeme.cc

================================================================================================================
*/






#include "Systeme.h"
//#include "Toupie.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

//Constructeurs -----------------------------------------------------------------
Systeme::~Systeme()  {

}

Systeme::Systeme() {}

Systeme::Systeme(vector<Toupie*> v, Integrateur* I, SupportADessin* s): Dessinable(s) {
  integrateur = I;
  for(size_t i(0) ; i < v.size() ; ++i) {
    tab.push_back(v[i]);
  }
}




//Accesseurs/Manipulateurs -------------------------------------
vector<Toupie*> Systeme::get_tab()  const {
  return tab;
}

void Systeme::set_tab(vector<Toupie*> v) {
  tab = v;
}


void Systeme::ajouter_toupie(Toupie* t) {
  if(t != nullptr) {
    tab.push_back(t);
  }
}

void Systeme::ajouter_integrateur(Integrateur* I) {
  integrateur = I;
}


//Méthodes diverses -----------------------------------------------------------------

ostream& Systeme::affiche(ostream& sortie) const {
  for(size_t i(0); i < tab.size(); ++i){
    sortie << "Toupie " << i+1 << " : " << endl;
    tab[i]->affiche(sortie);
    cout << endl;
  }
  return sortie;
}

ostream& Systeme::affiche_court(ostream& sortie) const {
  for(size_t i(0) ; i < tab.size() ; ++i) {
    sortie << "Dessin de la toupie " << i+1 << " : ";
    tab[i]->affiche_court(sortie);
  }
  return sortie;
}

ostream& operator<<(ostream& sortie, Systeme& s){
  return s.affiche(sortie);
}



void Systeme::evolue(double dt, double t_debut) {
//on ne peut pas simplement faire tab[j] = integrateur->integre(t_debut); car segmentation fault
  integrateur->set_dt(dt);



  for(size_t j(0) ; j < tab.size() ; ++j) {          // on itére ici sur les toupies en intégrant chacune des toupies dans la tableau
                                                     // ici on a qu'une seule boucle, car un seul intégrateur,mais cela sera ammené à changer plus tard dans le projet

     integrateur->set_toupie(tab[j]);


    Toupie* t = integrateur->integre(t_debut);

    tab[j] = t;



  }
}





void Systeme::dessine() {
    Supp->dessine(*this);
}


void Systeme::detruire_tout() {    // "Destructeur" global
  for (size_t i = 0; i < tab.size(); i++){
     delete tab[i];
     tab[i] = nullptr;
    }
   cout << 2 << endl;
    tab.clear();
    delete integrateur;
    integrateur = nullptr;
  cout << "destructeur systeme ok" << endl;
}


