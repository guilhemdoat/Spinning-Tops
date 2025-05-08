#include "ConeSimple.h"
#include "Systeme.h"
#include "text_viewer.h"
#include "IntEulCromer.h"
#include <iostream>

using namespace std;

int main() {
    Vecteur P(0.0,0.4,0.0), Pp(0.0, 0.0, 70.0);

    ConeSimple c(P, Pp, 0.1, 2, 0.9);

    IntegrateurEulerCromer I;

    vector<Integrateur*> tab({&I});

    vector<Toupie*> v({&c});

    TextViewer t(cout);

    Systeme s(v, tab, &t);

    s.dessine();


    for(double i(0) ; i < 1 ; i+=0.01) {
        cout << "Temps t = " << i << endl;
        s.evolue(0.01, 0, 0, 0);
        s.dessine();
    }

    s.detruire_tout();
}
