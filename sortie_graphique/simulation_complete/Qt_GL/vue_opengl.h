#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include <deque>
#include "Support.h"
#include "ConeSimple.h"

class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)

  virtual void dessine(Systeme const& s) override;

  // méthodes de (ré-)initialisation et de ré-ajustagement du point de vue
  void init();
  void initializePosition();
  void vuedecoteCentrale();
  void vuededessusDroite();
  void vuedecoteDroite();
  void vuededessusGauche();
  void vuedecoteGauche();
  void vuededessusarriere();
  void vuedecotearriere();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);
  
  // méthode utilitaire offerte pour simplifier
  void dessinePlan(QMatrix4x4 const& point_de_vue = QMatrix4x4() );

  void dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur);

  Vecteur trouve_normal(const Vecteur &v);

  void dessineCone(QMatrix4x4 const& point_de_vue, Vecteur& axe,
  Vecteur& sommet,  const double h, const double rb, const int n);

  void dessineTrace(QMatrix4x4 const& point_de_vue, std::deque<Vecteur> en_memoire);
  void gere_taille(std::array<std::deque<Vecteur>, 4> en_memoire);




 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;

  QMatrix4x4 matrice_vue;

  std::array<std::deque<Vecteur>, 4> memoire; // un tableau de tableau : pour chauqe toupie, ici 4, on y stock les positions du point G (centre de masse)
};

#endif
