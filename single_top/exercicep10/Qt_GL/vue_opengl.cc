#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "ConeSimple.h"
#include <cmath>
#include <vector>
#include "Toupie.h"
#include "Integrateur.h"
#include "IntEulCromer.h"
#include "Systeme.h"
#include "Vecteur.h"



// ======================================================================
void VueOpenGL::dessine(Systeme const& a_dessiner) //méthode de dessin principale qui dessine le système en évolution
{
    std::vector<Toupie*> v(a_dessiner.get_tab()); // on récupère le vector de Toupies du système
    QMatrix4x4 m;  //on créé une matrice qui sera la position de notre "tête de dessin"
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // on passe en mode dessin de polygones
    dessineAxes(m, true); // on dessine les axes en couleur, (d'où le true)

    dessinePlan(m); // On dessine le plan de roatation

    Vecteur vect(v[0]->trouve_axe()); // on cherche l'axe du cône


    Vecteur sommet(0.0,0.0,0.0); //on pose le sommet du cône à l'origine
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);// on repasse en blanc
    m.rotate(v[0]->get_P().get_coord(2)*(180/M_PI), v[0]->trouve_axe().get_coord(0), v[0]->trouve_axe().get_coord(1), v[0]->trouve_axe().get_coord(2)); //on applique la rotation à la matrice m pour dessiner le cône dans la position voulue
    dessineCone(m, vect, sommet, v[0]->get_L(), v[0]->get_r_base(), 25); // et enfin on dessine le cône en allant chercher toutes les caractéristiques voulues






};
// =======================================================================
void VueOpenGL::init()  // méthode d'initialisation non modifiée
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Compilation du shader OpenGL
  prog.link();

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition() //position initiale au dessus de la toupiee, pour voir le mouvment du centre de masse
{                                    //pour y revenir, appuyer sur "C"
  // position initiale

  matrice_vue.setToIdentity();   //on remet la matrice vue à l'identité afin de revenir à la position souhaitée indepemdemment des déplacements précédents
  matrice_vue.translate(0.0, 0.0, -4.0); // puis on "monte" la caméra de 4

}
//======================================================================

void VueOpenGL::vuedecote(){ // pour avoir une bonne vue de la toupie de coté (appuyer sur V)
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -4.0);
    matrice_vue.rotate(90.0, 1.0, 0.0, 0.0);// même procédé que pour la méthode pécédente, avec une rotation de 90 degrés selon x en plus
}



// ======================================================================
void VueOpenGL::translate(double x, double y, double z) //méthode de translation non modifiée
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z) // méthode de rotation non modifiée
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}


//======================================================================

void VueOpenGL::dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur) // dessin des axes. On a seulement inversé l'axe Y pour une meilleure visualisation
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_LINES);

  // axe X
  if (en_couleur) {
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  } else {
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  }
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);

  // axe Y
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);

  // axe Z
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, -1.0);

  glEnd();

}

// ======================================================================
void VueOpenGL::dessinePlan (QMatrix4x4 const& point_de_vue) //dessin du plan de roation
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS); // on passe en mode GL_QUADS

  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); //on dessine le plan en  rouge
  prog.setAttributeValue(SommetId, 1.0, 1.0, 0.0); // on place ensuite les 4 sommets du carré à dessiner dans le bon ordre
  prog.setAttributeValue(SommetId, -1.0, 1.0, 0.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, 0.0);
  prog.setAttributeValue(SommetId, 1.0, -1.0, 0.0);




 glEnd();
}

//========================================================================================

void VueOpenGL::dessineCone(QMatrix4x4 const& point_de_vue, Vecteur& axe, //fonction de dession du cône
Vecteur& sommet,  const double hauteur, const double rayon_base, const int nb_parts) {

    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    Vecteur v(1,0,0); // ce vecteur servira juste à créer la nouvelle base
    Vecteur centre_base = sommet + ( axe.oppose() * hauteur); // on trouve le centre de la base
    Vecteur x1 = axe^v;                     //on défini à l'aide des propriétés du produit vectoriel un nouveau repère orthogonal propre au cône
    Vecteur x2 = x1^axe;                    //formé des vecteurs axe(l'axe du cone), et des vecteurs x1 et x2, qui définissent le plan de la base.
    double en_radians = (360.0/nb_parts) * (M_PI/180.0); // on converti l'angle entre chaque part en radians


    std::vector<Vecteur> sommets_base;   //ici, on divise la base en n parts, dont on reliera plus tard les sommets
    for (int i = 0; i < nb_parts; ++i) {  // pour former des triangles. La base n'est donc pas un cercle parfait, et le cône plutôt
        double phi = en_radians * i;      // une pyramide, mais l'illusion est assez convaincante pour n grand.
        Vecteur p = centre_base + (((x1 * cos(phi)) + (x2 * sin(phi))) * rayon_base);
        sommets_base.push_back(p);// on ajoute ensuite tous les points ainsi trouvés dans un tableau
    }


    glBegin(GL_TRIANGLE_FAN);   //dessine n triangles avec un sommet commun (GL_TRIANGLE_FAN), on commence ici par les triangles de la "pointe"
    glVertex3d(sommet.get_coord(0), sommet.get_coord(1), sommet.get_coord(2)); // donne le sommet commun
    for (int i(0); i < nb_parts; ++i) { // on itère ensuite sur le nombre de parts
       glVertex3d(sommets_base[i].get_coord(0), sommets_base[i].get_coord(1), sommets_base[i].get_coord(2));// puis on va chercher les points du bord de labase pour les relier à la pointe
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); //et on dessine ici ceux de la base
    glVertex3d(centre_base.get_coord(0), centre_base.get_coord(1), centre_base.get_coord(2));// le sommet commun est ici le centre de la base
    for (int j(nb_parts-1); j >= 0; --j) {// on repart ici de la ou on s'est arreté a l'étape précédente, soit le dernier point dans sommet_base, que l'on relie maintenat au centre de la base
        glVertex3d(sommets_base[j].get_coord(0), sommets_base[j].get_coord(1), sommets_base[j].get_coord(2));
    }
    glEnd();
}





