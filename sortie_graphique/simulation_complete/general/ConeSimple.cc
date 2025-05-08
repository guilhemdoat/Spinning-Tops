#include "ConeSimple.h"
#include "Toupie.h"
#include <iostream>
#include <cmath>

using namespace std;

  //========================== constructeur =============================================
  ConeSimple::ConeSimple(Vecteur P, Vecteur P_point, double m, double l, double r) : Toupie(P, P_point), m_vol(m), L(l), r_base(r)
  {
      calcule();
  }

  ConeSimple::ConeSimple() {
      m_vol = r_base = L = 0;
  }

  //========================== accesseurs =================================================
  double ConeSimple::get_m_vol() const {
    return m_vol;
  }

  double ConeSimple::get_L() const {return L;}

  double ConeSimple::get_r_base() const { return r_base;}


  //========================= operateurs, affichage ========================================
  void ConeSimple::operator=(ConeSimple& toupie) {
      this->P = toupie.get_P().mod_2pi();
      this->P_point = toupie.get_P_point();
      this->r_base = toupie.get_r_base();
      this->L = toupie.get_L();
      this->m_vol = toupie.get_m_vol();
    }

  void ConeSimple::operator=(Toupie& toupie) {
        this->P = toupie.get_P().mod_2pi();
        this->P_point = toupie.get_P_point();
    }


  ostream& ConeSimple::affiche(ostream& sortie) const {
    Toupie::affiche(sortie);

    sortie << "masse volumique : " << this->m_vol << endl;

    sortie << "rayon de la base : " << this->get_r_base() << endl;

    sortie << "Hauteur : " << this->get_L() << endl;

    return sortie;
  }

  ostream& ConeSimple::affiche_invariants(ostream& sortie) const {
        sortie << endl;
        sortie << "Energie totale : " << energie << endl;
        sortie << "Projection sur k du moment cinétique en A : " << LA_k << endl;
        sortie << "Projection sur a du moment cinétique en A : " << LA_a << endl;
        sortie << "Produit mixte [ omega, L, a ] : " << produit_mixte << endl;

        return sortie;
    }


  //========================== calcul de valeurs caracteristiques =======================================

      void ConeSimple::calcule() {
          calcule_autres();
          calcule_invariants();
      }


     void ConeSimple::calcule_invariants() {
      energie = calcule_energie();
      LA_k = calcule_LA_k();
      LA_a = calcule_LA_a();
      produit_mixte = calcule_produit_mixte();
    }

    double ConeSimple::calcule_energie() const {
      const Vecteur OG_ref_G({0,0,L*3/4}); // OG = (3/4)*L.â en supposant que O et A sont au meme endroit et que G se situe sur l'axe principal de la toupie
      const Vecteur g_ref_G = matrice_passage*g;
      return omega*LA_moment/2 - masse*(g_ref_G*OG_ref_G);
    }


    double ConeSimple::calcule_LA_k() const { // = LA.k : il faut exprimer k en fonction du sys de coord (u, b, a) par la matrice de passage
      Vecteur k_ref_O(0,0,1); //Vecteur unitaire k dans le referentiel (et donc sys de coord) RO
      Vecteur k_ref_G = matrice_passage*k_ref_O; //Vecteur unitaire k dans le sys de coord RG = (G, û, ^b, â)

      return LA_moment*k_ref_G;
    }


    double ConeSimple::calcule_LA_a() const {
      Vecteur a_ref_G(0,0,1);
      return LA_moment*a_ref_G; //LA_a = 3eme coordonnee de LA
    }


    double ConeSimple::calcule_produit_mixte() const { //voir description dans la declaration des attributs
      Vecteur a_ref_G(0,0,1);
      return a_ref_G*(omega^L_moment);
    }


    void ConeSimple::calcule_autres() //pour calculer toutes les autres valeurs non-invariantes de mouvemen
    {
      masse = M_PI*m_vol*r_base*r_base*L/3;

      I1 = (r_base*r_base+L*L/4)*3*masse/20;
      I3 = 3*masse*r_base*r_base/10;
      IA1 = 3*masse*(r_base*r_base/20 + L*L/5);
      IA3 = I3;

      Matrice33 m1(I1, I1, I3);
      I = m1;
      Matrice33 m2(IA1, IA1, IA3);
      IA = m2;

      //omega = (theta_p, psi_p*sin(theta), psi_p*cos(theta) +phi_p, dans le repere RG = (G, û, ^b, â)
      Vecteur v7(P_point.get_coord(1), P_point.get_coord(0)*sin(P.get_coord(1)), P_point.get_coord(0)*cos(P.get_coord(1)) + P_point.get_coord(2) );
      omega = v7;

      //moment cinetique en A = IA*omega car vitesse en A = 0; on fait tout cela dans le repere RG = (G, û, ^b, â)
      LA_moment = IA*omega;
      L_moment = I*omega;

      matrice_passage = calcule_matrice_passage(); // matrice de passage du referentiel RG au referentiel RO
    }



   //==================== equation differentielle de la toupie ============================================
   Vecteur ConeSimple::f(double t, Vecteur Pn, Vecteur P_pointn) {
     //dans l'ordre : psi, theta, phi
     double d = L*3/4 ;//d = ||AG|| avec G le centre de masse, A le point de contact
    double m = M_PI*m_vol*r_base*r_base*L/3;
    double I3 = 3*m*r_base*r_base/10;
    double Ia1 = 3*m*(r_base*r_base/20 + L*L/5);

    //pour alleger les ecritures de psipp, thetapp et phipp
    double theta = Pn.get_coord(1);
    double psi_P = P_pointn.get_coord(0);
    double theta_P = P_pointn.get_coord(1);
    double phi_P = P_pointn.get_coord(2);
    

    double psi_PP = ((I3-2*Ia1)*psi_P*cos(theta)+I3*phi_P)*theta_P/(Ia1*sin(theta));

    double theta_PP = (m*g_scalaire*d*sin(theta) + psi_P*sin(theta)*((Ia1-I3)*psi_P*cos(theta)-I3*phi_P))/Ia1;

    double phi_PP = ((Ia1-(I3-Ia1)*cos(theta)*cos(theta))*psi_P-I3*phi_P*cos(theta))*theta_P/(Ia1*sin(theta));

    Vecteur v(psi_PP, theta_PP, phi_PP);
    return v;
  }


