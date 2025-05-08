#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>


#include "constante.h"
#include "Dessinable.h"
#include "Integrateur.h"
#include "IntEulCromer.h"
#include "Matrice33.h"
#include "Support.h"
#include "Systeme.h"
#include "Toupie.h"
#include "Vecteur.h"
#include "text_viewer.h"
#include "ConeSimple.h"

using namespace std;





int main() {

  TextViewer ecran(cout);
  double dt(0.01);

  Vecteur P(0,M_PI/6,0), Pp(0, 0, 60);
  ConeSimple c1(P, Pp, 0.1, 1.5, 0.5);
  vector<Toupie*> v({&c1});
  IntegrateurEulerCromer I(dt, &c1);
  vector<Integrateur*> t({&I});

  Systeme s(v, t, &ecran);

  s.affiche_invariants(cout);
  s.dessine();



  cout << endl;
    for(int i(0) ; i<30 ; ++i) {
      double x((i+1)*dt);
        cout << "Temps : t="  << x << endl;
        s.evolue(dt, i*dt, 0, 0);

        s.affiche_invariants(cout);
        s.dessine();
        cout << endl << endl;
    }



  cout << endl;
  s.detruire_tout();



}



