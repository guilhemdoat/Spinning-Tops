#ifndef CONTENU_H
#define CONTENU_H

#include "Dessinable.h"
#include "Support.h"

class Contenu : public Dessinable {
public:
  Contenu(SupportADessin* vue)
    : Dessinable(vue), angle(0.0)
  {}
  virtual ~Contenu() {}

  Contenu() {}

  virtual void dessine() override
  { Supp->dessine(*this); }

  void evolue(double dt) override;

  // accesseur
  double infos() const { return angle; }

private:
  double angle; /* pour le mouvement ;
                   dans cet exemple, juste une rotation
                   au cours du temps                    */
};

#endif // CONTENU_H
