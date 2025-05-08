#define _USE_MATH_DEFINES

#include <QApplication>
#include "glwidget.h"
#include "IntEulCromer.h"
#include "intnewmark.h"
#include "ConeSimple.h"
#include "Vecteur.h"
#include "Systeme.h"
#include <vector>
#include "vue_opengl.h"
#include "toupiegenerale.h"
#include "integrateurrungekutta.h"
#include <cmath>

int main(int argc, char* argv[])
{


    double dt(0.01); // le pas de temps utilisé dans la simulation

    Vecteur P(0.0,0.4,0.0), Pp(0.0, 0.0, 70.0);


/*

    ConeSimple* c2 = new ConeSimple(P, Pp, 0.1, 2, 0.9); //IntegrateurEulerCromer
    ConeSimple* c3 = new ConeSimple(P, Pp, 0.1, 2, 0.9); //IntegrateurNewMark
    ConeSimple* c4 = new ConeSimple(P, Pp, 0.1, 2, 0.9); //IntegrateurRungeKutta

    IntegrateurEulerCromer* I = new IntegrateurEulerCromer(dt,c2 );
    IntegrateurNewmark* I2 = new IntegrateurNewmark(dt, c3);
    IntegrateurRungeKutta* I3 = new IntegrateurRungeKutta(dt, c4);

    std::vector<Toupie*> tab({c2, c3, c4});
    std::vector<Integrateur*> t({I, I2, I3});
*/
// on créer domc 4 toupies: 3 cônes simples et une toupie généralisée
    ConeSimple c1(P, Pp, 0.1, 2, 0.9);
    ConeSimple c2(P, Pp, 0.1, 2, 0.9);
    ConeSimple c3(P, Pp, 0.1, 2, 0.9);
    ToupieGenerale c4(P, Pp, 0.1, 2, 0.9);

// puis 4 intégrateur, 1 par toupie
    IntegrateurEulerCromer integ(dt, &c1);
    IntegrateurNewmark integ3(dt, &c2);
    IntegrateurRungeKutta integ2(dt, &c3);
    IntegrateurEulerCromer integ4(dt, &c4);



    std::vector<Toupie*> tab({&c1, &c2, &c3, &c4});// on créer nos 2 vectors, attributs de notre Système
    std::vector<Integrateur*> tab_I({&integ, &integ2, &integ3, &integ4});



  QApplication a(argc, argv);
  GLWidget w(tab, tab_I); // on construit notre GLWidget
  w.setWindowTitle("Simulation De Toupies");
  w.show();

  return a.exec(); // et on rentre dans la boucle

}
;
