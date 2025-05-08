
/*
================================================================================================================

Systeme.h

================================================================================================================
*/
#pragma once
#include<vector>
#include "Toupie.h"
#include "Integrateur.h"
#include "Support.h"
#include "Dessinable.h"




class Systeme: public Dessinable {
protected :

  std::vector<Toupie*> tab;
  Integrateur* integrateur; // A ce moment du projet, nous n'avons qu'un seul intégrateur de disponible, et donc Système n'en prend qu'un seul en attribut


public :

  //constructeur, destructeur ----------------------

  Systeme();

  Systeme(std::vector<Toupie*> v, Integrateur* I, SupportADessin* s);

  ~Systeme();

 //Accesseurs, Manipulateurs ----------------------------------
  std::vector<Toupie*> get_tab() const;
  void set_tab(std::vector<Toupie*> v);

   //Méthodes diverses ------------------------------------------
  void ajouter_toupie(Toupie* t); // ajoute un pointeur vers une toupie a tab

  void ajouter_integrateur(Integrateur* I);// ajoute un Intégrateur

  std::ostream& affiche(std::ostream& sortie) const; // deux méthodes d'affichage
  std::ostream& affiche_court(std::ostream& sortie) const;

  virtual void evolue(double dt, double t_debut) override; //  redéfinition de evolue de Dessinable

  virtual void dessine() override; // redéfinition de dessine de Dessinable

  void detruire_tout();



};

 std::ostream& operator<<(std::ostream& sortie, Systeme const& s);
