#include "integrateurrungekutta.h"
#include "Integrateur.h"

Toupie* IntegrateurRungeKutta::integre(double t_debut) {// on implémente ici la fonction intègre() en utilisant les formules données dans le complément mathématique
    Vecteur P_point_n_1(toupie->get_P_point()), Pn_1(toupie->get_P());
    double t_autre = t_debut+dt/2;

    k1 = P_point_n_1;
    kp1 = toupie->f(t_debut, Pn_1, P_point_n_1);
    k2 = P_point_n_1 + ((kp1*dt)*0.5);
    kp2 = toupie->f(t_autre, Pn_1 + ((k1*dt)*0.5), P_point_n_1 + ((kp1*dt)*0.5));
    k3 = P_point_n_1 + ((kp2*dt)*0.5);
    kp3 = toupie->f(t_autre, Pn_1 + ((k2*dt)*0.5), P_point_n_1 + ((kp2*dt)*0.5));
    k4 = P_point_n_1 + (kp3*dt);
    kp4 = toupie->f(t_debut, Pn_1 + (k3*dt), P_point_n_1 + (kp3*dt));


    toupie->set_P(Pn_1 + (((k1+(k2*2)+(k3*2)+k4)*dt)*(1.0/6.0)));
    toupie->set_P_point(P_point_n_1 + (((kp1+(kp2*2)+(kp3*2)+kp4)*dt)*(1.0/6.0)));



    return toupie;

}

