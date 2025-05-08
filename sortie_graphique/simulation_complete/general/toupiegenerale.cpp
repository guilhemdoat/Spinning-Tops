#define _USE_MATH_DEFINES


#include "toupiegenerale.h"
#include "constante.h"
#include "ConeSimple.h"
#include "Matrice33.h"
#include <iostream>

#include <cmath>


//constructeur
ToupieGenerale::ToupieGenerale(Vecteur P, Vecteur P_point, double m, double l, double r) : ConeSimple(P, P_point, m, l, r)
{}


//equa. diff.
Vecteur ToupieGenerale::f(double t, Vecteur P, Vecteur P_point) {

    //En utilisant le thm. de Huygens-Steiner, dans le repere u, b, a, avec xAG=yAG=0, zAG=L*3/4 :
    Vecteur tmp(masse*g_scalaire*sin(P.get_coord(1))*L*3/4, 0, 0);
    Vecteur MA = tmp;

    Vecteur a_unitaire(0,0,1); //dans le repere (G,u,b,a)
    Vecteur omega_e(omega - a_unitaire*P_point.get_coord(2)); //page 5 complement maths
    Matrice33 delta((L*3/4)*(L*3/4), (L*3/4)*(L*3/4), 0);  //sect. 3.2 page 7
    Matrice33 IA(I + masse*delta);
    Vecteur omega_point((IA.inv())*(MA-(omega_e^(IA*omega)))); //equ. (9) page 11 complement maths, en supposant IA point = 0

    //pour alleger l'ecriture dans les formules pour thetapp, psipp, phipp
    double theta = P.get_coord(1);
    double psi_P = P_point.get_coord(0);
    double theta_P = P_point.get_coord(1);

    if(std::abs(theta) < 1e-10 || std::abs(theta - M_PI) < 1e-10) {
        Vecteur out(0, omega_point.get_coord(0), omega_point.get_coord(2));
        return out;
    }

    double psi_P_P = (omega_point.get_coord(1)-psi_P*theta_P*cos(theta))/sin(theta);
    double theta_P_P = omega_point.get_coord(0);
    double phi_P_P = omega_point.get_coord(2) + (psi_P*theta_P-omega_point.get_coord(1)*cos(theta))/sin(theta);



    Vecteur out(psi_P_P, theta_P_P, phi_P_P);
    return out;
}

std::ostream& ToupieGenerale::affiche(std::ostream &sortie) const {
    sortie << "Toupie Generale : " << std::endl;
    ConeSimple::affiche(sortie);
    return sortie;
}
