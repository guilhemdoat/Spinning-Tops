#include <iostream>
#include "Vecteur.h"
#include <string>
#include <vector>

using namespace std;


int main() {


  // un vecteur en 3D :
Vecteur vect1(1.0, 2.0, -0.1);

// un autre vecteur en 3D
Vecteur vect2(2.6, 3.5,  4.1);

Vecteur vect3(vect1);  // copie de V1
Vecteur vect4({-1.0, 0.5});

cout << "Vecteur 1 : " << vect1 << endl;
cout << "Vecteur 2 : " << vect2 << endl;
cout << "Vecteur 3 : " << vect3 << endl;
cout << "Vecteur 4 : " << vect4 << endl;

cout << "Le vecteur 1 est ";
if (vect1 == vect2) {
    cout << "égal au";
} else {
    cout << "différent du";
}
cout << " vecteur 2," << endl << "et est ";
if (vect1 != vect3) {
    cout << "différent du";
} else {
    cout << "égal au";
}
cout << " vecteur 3." << endl;



  cout << endl << endl;

  cout << "Oppose de v1 : ";
  cout << (vect1.oppose()) << endl;

  cout << vect1 << " +  " << vect2 << " =  " << vect1+vect2 << endl;

  cout << vect1 << " +  " << vect4 << " =  " << vect1+vect4 << endl;

  cout << vect1 << " -  " << vect2 <<  " =  " << vect1-vect2 << endl;

  cout << vect1 << " *  " << vect2 << " =  " << vect1*vect2 << endl;

  cout << "Produit vectoriel de v1 et v2 : ";
  cout << (vect1^vect2) << endl;

  cout << "3*" << vect1 << " = " <<vect1*3 << endl;

  cout << "Norme de v1 : " << vect1.norme() << endl;

  cout << "Norme au carre de v1 : " << vect1.norme2() << endl;


  Vecteur a(1, 1, 1);
  Vecteur direction( ~a ); // utilisation de l'opérateur unaire ~
  cout << "Vecteur " << a << " normé : " << direction << endl;

  try {
    cout << "Produit vectoriel de " << vect1 << " et " << vect4 << " : " <<(vect1^vect4) << endl;
  }
  catch(const string s) {
    cerr <<  s << endl;
  }



}
