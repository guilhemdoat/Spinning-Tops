#include "intnewmark.h"
#include "Toupie.h"
#include <cmath>


//integrateur
Toupie* IntegrateurNewmark::integre(double t) {
    double t_avant = t-dt; //inutile en soi car le temps n'entre jamais en compte dans la fonction f
    //mais aide a comprendre le code

    Vecteur P_point_n_1(toupie->get_P_point()), Pn_1(toupie->get_P());
    Vecteur P_point_n(P_point_n_1), Pn(Pn_1);

    s = toupie->f(t_avant, Pn_1, P_point_n_1);
    Vecteur n;
    do {
        q = Pn;
        r = toupie->f(t, Pn, P_point_n);
        P_point_n = P_point_n_1+((r+s)*(dt*0.5));
        Pn = Pn_1 + (P_point_n_1*dt)+ (((r*0.5) + s)*(dt*dt*(1.0/3.0)));

        n = Pn - q;

    }while(n.norme()>= eps);

    toupie->set_P(Pn);
    toupie->set_P_point(P_point_n);

    return toupie;
}



//constructeurs, destructeur

IntegrateurNewmark::IntegrateurNewmark() {};
IntegrateurNewmark::~IntegrateurNewmark() {};
IntegrateurNewmark::IntegrateurNewmark(double dt, Toupie* t, double epsilon): Integrateur(dt, t) , eps(epsilon){}
