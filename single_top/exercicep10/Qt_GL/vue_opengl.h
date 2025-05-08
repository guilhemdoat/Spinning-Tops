#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include <deque>
#include "Support.h"
#include "ConeSimple.h"

class VueOpenGL : public SupportADessin {
 public:
  virtual void dessine(Systeme const& s) override; // on override ici la méthode dessine de la super classe SupportADessin

  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();
  void vuedecote();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);
  
  // méthode utilitaire offerte pour simplifier
  void dessinePlan(QMatrix4x4 const& point_de_vue = QMatrix4x4() ); // dessine le pan sur lequel la toupie tourne selon l'endroti indiqué par la QMatrix passée en argument

  void dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur); //dessine les axes de la même manière

  void dessineCone(QMatrix4x4 const& point_de_vue, Vecteur& axe,  //dessine un cône de la même manière
  Vecteur& sommet,  const double h, const double rb, const int n);




 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;

  QMatrix4x4 matrice_vue;
};

#endif
