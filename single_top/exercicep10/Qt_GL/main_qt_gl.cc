#include <QApplication>
#include "glwidget.h"
#include "IntEulCromer.h"
#include "ConeSimple.h"
#include "Vecteur.h"
#include "Systeme.h"
#include <vector>
#include "vue_opengl.h"

int main(int argc, char* argv[])
{


    Vecteur P(0.0,0.4,0.0), Pp(0.0, 0.0, 70.0);                                 //On initialise ici la toupie que l'on va faire evoluer, ici donc un cône simple
    ConeSimple* c2 = new ConeSimple(P, Pp, 0.1, 2.0, 0.9);
    IntegrateurEulerCromer* integ = new IntegrateurEulerCromer(0.01, c2);        // et ici l'intégrateur que l'on va utiliser, ici un IntegrateurEulerCromer

    std::vector<Toupie*> tab;                      //puis on créé un vector de toupie dans lequel on push_back la toupie préalablement créée
    tab.push_back(c2);





  QApplication a(argc, argv);
  GLWidget w(tab, integ);   //on construit alors notre GLWidget avec les élements nécessaires
  w.setWindowTitle("Exercice P10");
  w.show();

  return a.exec(); // et enfin on rentre dans la boucle
}
