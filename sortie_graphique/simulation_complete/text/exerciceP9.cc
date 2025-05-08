#include <iostream>
#include <cmath>
#include <vector>


#include "IntEulCromer.h"
#include "Systeme.h"
#include "Vecteur.h"
#include "text_viewer.h"
#include "ConeSimple.h"

using namespace std;





int main() {

  TextViewer ecran(cout);
  double dt(0.01);

  Vecteur P(0,M_PI/6,0), Pp(0, 0, 60);
  Vecteur P2(0, 0, 0.785398), Pp2(0, 0, 40);
  ConeSimple c1(P, Pp, 0.1, 1.5, 0.5);
  ConeSimple c2(P2, Pp2, 0.1, 1.5, 0.5);
  vector<Toupie*> v({&c1, &c2});
  IntegrateurEulerCromer I(dt, &c1);
  vector<Integrateur*> t({&I});

  Systeme s(v, t, &ecran);

  s.affiche(cout);


  cout << endl;
    for(int i(0) ; i<30 ; ++i) {
      double x((i+1)*dt);
        cout << "Temps : t="  << x << endl;
        s.evolue(dt, i*dt, 0, 0);
        s.evolue(dt, i*dt, 1, 0);

        s.dessine();
        cout << endl << endl;
    }



  cout << "On a tout affiche" << endl;
  s.detruire_tout();


}


