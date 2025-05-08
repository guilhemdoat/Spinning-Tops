
#include "ConeSimple.h"
#include "Vecteur.h"
#include "Toupie.h"
#include <iostream>

using namespace std;




int main() {

  Vecteur P(1, 5, 2), Pp(3, 7, 1);
  ConeSimple c1(P, Pp, 0.1, 1.5, 0.5);

  c1.affiche(cout);

  //la classe toupie etant abstraite on ne peut que creer et afficher un ConeSimple
}

