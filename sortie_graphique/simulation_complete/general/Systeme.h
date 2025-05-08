#pragma once
#include<vector>
#include "Toupie.h"
#include "Support.h"
#include "Dessinable.h"
#include "constante.h"
#include "integrateurrungekutta.h"
#include "intnewmark.h"
#include "IntEulCromer.h"




class Systeme: public Dessinable { //Un systeme est un dessinable
protected :

  std::vector<Toupie*> tab; //Tableau de pointeurs vers des toupies
  std::vector<Integrateur*> tab_integ;

public :

  //constructeurs, destructeur ----------------------

  Systeme();

  Systeme(std::vector<Toupie*> v, std::vector<Integrateur*>, SupportADessin* s);

  ~Systeme();

  //===================== accesseurs, manipulateurs ==================================
  std::vector<Toupie*> get_tab() const;
  void set_tab(std::vector<Toupie*> v);

  void ajouter_toupie(Toupie* t); // ajoute un pointeur vers une toupie a tab

  void ajouter_integrateur(Integrateur* I);


  //======================= operateurs de sortie ========================================
  std::ostream& affiche(std::ostream& sortie) const;
  std::ostream& affiche_court(std::ostream& sortie) const;
  std::ostream& affiche_invariants(std::ostream& sortie) const;

  //====================== methodes diverses ========================================
  virtual void evolue(double dt, double t_debut, size_t indice_toupie, size_t indice_integ) override; //fait evoluer toutes les toupies d'un pas de temps

  virtual void dessine() override; //affiche le systeme

  void detruire_tout(); //desalloue les pointeurs



};

//operateur de sortie qui utilise la methode affiche
 std::ostream& operator<<(std::ostream& sortie, Systeme const& s);
