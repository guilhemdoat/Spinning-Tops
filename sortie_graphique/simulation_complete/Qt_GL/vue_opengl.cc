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
void VueOpenGL::dessine(Systeme const& a_dessiner) //méthode de dessin principale
{
    std::vector<Toupie*> v(a_dessiner.get_tab());// on récupère le vector de toupie
    QMatrix4x4 m; // on créer une QMatrix4x4 qui sera notre "tête de dessin"
    Vecteur sommet(0.0,0.0,0.0); // et un point qui sera le sommet de nos cônes
    std::vector<Vecteur> vect; //on créer un vector de Vecteur, pour y mettre nos axes
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // on passe en dessin polygône
    dessineAxes(m, true);// on dessine les axes
    dessinePlan(m);// et notre plan de rotation

    for( auto v : a_dessiner.get_tab()){ // on range nos axes dans le tableau, en les trouvant avec trouve_axe()
        vect.push_back(v->trouve_axe());
    }


    for(size_t i(0); i < a_dessiner.get_tab().size(); ++i){ // à chaque étape, on récupère la position du centre de masse de chaque toupie, et on le range dans le deque prévu à cet effet
        Vecteur G(v[i]->trouve_axe().get_coord(0), v[i]->trouve_axe().get_coord(1), v[i]->trouve_axe().get_coord(2));
        Vecteur VraiG = G*(-0.75*v[i]->get_L());
        this->memoire[i].push_back(VraiG);
    }


    for(size_t j(0); j < a_dessiner.get_tab().size(); ++j){ // et enfin on rentre dans la boucle de dessin des toupies
        if(j == 0){
            m.translate(-3.0,0.0,0.0); //en supposant que notre systeme ait quatre toupies, on replace manuellement chaque toupie
        }                              //une à droite, une à gauche, une au centre, et une à l'arrière
        if( j == 2){
            m.translate(3.0,0.0,0.0);
        }
        if ( j==3 ){
            m.translate(0.0, 3.0, 0.0);

        }


        dessineTrace(m,this->memoire[j]); // on dessine la trace(en bleu, voir dessineTrace())
        prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // on repasse en blanc
        m.rotate(v[j]->get_P().get_coord(2)*(180/M_PI), v[j]->trouve_axe().get_coord(0), v[j]->trouve_axe().get_coord(1), v[j]->trouve_axe().get_coord(2)); // on imprime la rotation, en convertissant bien la 2eme coordonnée de P (theta)en radians
        dessineCone(m, vect[j], sommet, v[j]->get_L(), v[j]->get_r_base(), 25);//on dessine le cone représentant le ConeSimple ou la ToupieGenerale, en allant chercher les bonnes grandeurs aux bons endroits
        m.setToIdentity(); // on revient à l'origine pour la toupie suivante

     }

 gere_taille(this->memoire); // on vérifie enfin que la taille des tableaux contenant les positions des centres de masses ne soit pas trop "remplis"

 //std::cout << a_dessiner.get_tab()[0]->get_P() << std::endl;


}
// =======================================================================
void VueOpenGL::init() //méthode init non modifiée
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

  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, 0.0, -5.0);

}
//Commande de la caméra =================================================================================

void VueOpenGL::vuedecoteCentrale(){ // pour avoir une bonne vue de la toupie centrale de coté (appuyer sur V)
    matrice_vue.setToIdentity(); //on revient à l'origine. Ainsi, la commande donne le même résulat où que la caméra soit
    matrice_vue.translate(0.0, 0.0, -5.0); // on prend un peu de hauteur
    matrice_vue.rotate(270.0, 1.0, 0.0, 0.0); // on effectue 3/4 de tour autour de x, pour éviter que la caméra soit dans la toupie à l'arrière
    matrice_vue.rotate(180, 0.0, 1.0 ,0.0); // et on retourne la vue, car la rotation précédente nous à mis à l'envers
}

void VueOpenGL::vuededessusDroite(){ // pour avoir une bonne vue de la toupie de droite de dessus (appuyer sur B)
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -5.0);
    matrice_vue.translate(-3.0,0.0,0.0);

}

void VueOpenGL::vuedecoteDroite(){ // pour avoir une bonne vue de la toupie droite de coté (appuyer sur N)
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -5.0);
    matrice_vue.translate(-3.0,0.0,0.0);
    matrice_vue.rotate(90.0, 1.0, 0.0, 0.0);

}

void VueOpenGL::vuededessusGauche(){ // pour avoir une bonne vue de la toupie de gauche de dessus (appuyer sur Z)
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -5.0);
    matrice_vue.translate(3.0,0.0,0.0);

}

void VueOpenGL::vuedecoteGauche(){  // pour avoir une bonne vue de la toupie de gauche de coté (appuyer sur X)
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -5.0);
    matrice_vue.translate(3.0,0.0,0.0);
    matrice_vue.rotate(90.0, 1.0, 0.0, 0.0);
}

void VueOpenGL::vuededessusarriere(){ // pour avoir une bonne vue de la toupie arrière de dessus (appuyer sur G)
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -5.0);
    matrice_vue.translate(0.0,-3.0,0.0);

}

void VueOpenGL::vuedecotearriere(){ // pour avoir une bonne vue de la toupie arrière de coté (appuyer sur H)
    matrice_vue.setToIdentity();
    matrice_vue.translate(0.0, 0.0, -5.0);
    matrice_vue.rotate(90.0, 0.0, 1.0, 0.0);
    matrice_vue.rotate(90.0, 1.0, 0.0, 0.0);
    matrice_vue.translate(0.0,-3.0,0.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z) // méthode translate non modifiée
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
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z) // méthode rotate non modifiée
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}


//======================================================================

void VueOpenGL::dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur) // méthode de dessin des axes non modifiée
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
  prog.setAttributeValue(SommetId, 2.0, 0.0, 0.0);

  // axe Y
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 2.0, 0.0);

  // axe Z
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, -2.0);

  glEnd();

}

//========================================================================

void VueOpenGL::dessineTrace(QMatrix4x4 const& point_de_vue, std::deque<Vecteur> en_memoire){ // méthode de dessin de la trace

    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue); //on place la "tete de dessin"

    glBegin(GL_POINTS);  // on passe en mode GL_POINTS
    for( auto previous_pos : en_memoire){ // on fait une boucle sur les points du tableau en argument
        prog.setAttributeValue(CouleurId, 0.0, 0.5, 0.5); // on les dessine en bleu pour qu'ils se voient bien
        prog.setAttributeValue(SommetId, previous_pos.get_coord(0), previous_pos.get_coord(1), previous_pos.get_coord(2));
        }
    glEnd();
}

//========================================================================

void VueOpenGL::gere_taille(std::array<std::deque<Vecteur>, 4> en_memoire){ // méthode de contrôle de la taille de la mémoire contenant les points, afin que la liste à parcourir ne soit pas trop longue, ce qui pourrait avoir un impact sur la fluidité de la simulation
   for( auto memoire : en_memoire){
    if(memoire.size() > 3000){
        memoire.pop_front(); // on supprime les 1ers points du tableau, qui sont en suite remplacé par de nouveaux
    }
   }

}

// ======================================================================
void VueOpenGL::dessinePlan (QMatrix4x4 const& point_de_vue) //méthode de dessin du plan de rotation
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS); // on passe en mode GL_QUADS

  // on donne ensuite les coordonnées des 4 sommets dans le bon ordre
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, 3.0, 3.0, 0.0);
  prog.setAttributeValue(SommetId, -3.0, 3.0, 0.0);
  prog.setAttributeValue(SommetId, -3.0, -3.0, 0.0);
  prog.setAttributeValue(SommetId, 3.0, -3.0, 0.0);


 glEnd();
}

//========================================================================================

void VueOpenGL::dessineCone(QMatrix4x4 const& point_de_vue, Vecteur& axe,
Vecteur& sommet,  const double hauteur, const double rayon_base, const int nb_parts) { // méthode de dessin de cône

    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    Vecteur v(1,0,0);
    Vecteur centre_base = sommet + ( axe.oppose() * hauteur);
    Vecteur x1 = axe^v;                     //on défini à l'aide des propriétés du produit vectoriel un nouveau repère orthogonal propre au cône
    Vecteur x2 = x1^axe;                    //formé des vecteurs axe(l'axe du cone), et des vecteurs x1 et x2, qui définissent le plan de la base.
    double en_radians = (360.0/nb_parts) * (M_PI/180.0);


    std::vector<Vecteur> sommets_base;   //ici, on divise la base en n parts, dont on reliera plus tard les sommets
    for (int i = 0; i < nb_parts; ++i) {  // pour former des triangles. La base n'est donc pas un cercle parfait, et le cône plutôt
        double phi = en_radians * i;      // une pyramide, mais l'illusion est assez convaincante pour n grand.
        Vecteur p = centre_base + (((x1 * cos(phi)) + (x2 * sin(phi))) * rayon_base);
        sommets_base.push_back(p);
    }


    glBegin(GL_TRIANGLE_FAN);   //dessine n triangles avec un sommet commun (GL_TRIANGLE_FAN), on commence ici par les triangles de la "pointe"
    glVertex3d(sommet.get_coord(0), sommet.get_coord(1), sommet.get_coord(2)); // donne le sommet commun
    for (int i = 0; i < nb_parts; ++i) {
       glVertex3d(sommets_base[i].get_coord(0), sommets_base[i].get_coord(1), sommets_base[i].get_coord(2));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN); //et on dessine ici ceux de la base
    glVertex3d(centre_base.get_coord(0), centre_base.get_coord(1), centre_base.get_coord(2));
    for (int i = nb_parts-1; i >= 0; --i) {
        glVertex3d(sommets_base[i].get_coord(0), sommets_base[i].get_coord(1), sommets_base[i].get_coord(2));
    }
    glEnd();
}





