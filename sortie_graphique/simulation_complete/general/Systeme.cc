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



//================================= accesseurs, manipulateurs ==========================================

void Systeme::ajouter_toupie(Toupie* t) {
  if(t != nullptr) tab.push_back(t);

}

void Systeme::ajouter_integrateur(Integrateur* I) {
    if(I != nullptr) tab_integ.push_back(I);
}


vector<Toupie*> Systeme::get_tab()  const {
  return tab;
}

void Systeme::set_tab(vector<Toupie*> v) {
  tab = v;
}



// =========================== constructeurs, destructeur ===================================
Systeme::Systeme(vector<Toupie*> v, vector<Integrateur*> t, SupportADessin* s): Dessinable(s) {
    for(auto i: v) {
        tab.push_back(i);
    }
    for(auto j: t) {
        tab_integ.push_back(j);
    }
}


Systeme::~Systeme()  {}

Systeme::Systeme() {}


// ============================ sortie ======================================
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

ostream& Systeme::affiche_invariants(ostream& sortie) const {
  for(size_t i(0) ; i < tab.size() ; ++i) {
    sortie <<std::endl << "Invariants de la toupie #" << i+1 << " : ";
    tab[i]->affiche_invariants(sortie);
  }
  return sortie;
}

ostream& operator<<(ostream& sortie, Systeme& s){
  return s.affiche(sortie);
}




// ================================ methodes diverses ==============================================

//fait evoluer la toupie en position indice_toupie du pas de temps dt avec l'integrateur en position indice_integ
void Systeme::evolue(double dt, double t_debut, size_t indice_toupie, size_t indice_integ) {

  //on verifie que les valeurs indice_toupie et indice_integ sont utilisables
  if(indice_toupie >= tab.size()) throw string("Erreur dans l'appel de la methode Systeme::evolue : l'indice de la toupie est superieur a la taille du tableau");
  if(indice_integ >= tab_integ.size()) throw string("Erreur dans l'appel de la methode Systeme::evolue : l'indice de l'integrateur est superieur a la taille du tableau");

  //on lie l'integrateur a la toupie, on lui donne une bonne valeur de dt et on integre la toupie
  tab_integ[indice_integ]->set_toupie(tab[indice_toupie]);
  tab_integ[indice_integ]->set_dt(dt);
  tab[indice_toupie] = tab_integ[indice_integ]->integre(t_debut);

  //on recalcule les invariants de la toupie
  tab[indice_toupie]->calcule();


}






void Systeme::dessine() {
    Supp->dessine(*this);
}


void Systeme::detruire_tout() {
  //desalloue les toupies
  for (size_t i = 0; i < tab.size(); i++){
     delete tab[i];
     tab[i] = nullptr;
    }
  tab.clear();

  for (size_t i = 0; i < tab_integ.size(); i++){
     delete tab_integ[i];
     tab_integ[i] = nullptr;
    }
  tab_integ.clear();
  cout << "destructeur systeme ok" << endl;
}


