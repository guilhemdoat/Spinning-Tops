#pragma once
#include <vector>
#include <iostream> //pour operator<<








bool compare_(double x, double y, double precision);


class Vecteur {
private :
    std::vector<double> v;
    unsigned int compteur;

public:

//----------------------------------------------
    //constructeurs
    Vecteur(); //constructeur par defaut

    Vecteur(int const& dim); //pour les matrices, on utilise que des vecteurs de dim = 3


  Vecteur(std::initializer_list<double> const& liste);


  Vecteur(double x, double y, double z);

  Vecteur(Vecteur const& autre);
//---------------------------------------------


//------------------------------------------------
  //Accesseurs/Manipulateurs

    std::vector<double> get_vect() const;

    void augmente(const double& valeur); // ajoute une cordonne au vecteur

    double get_coord(int pos) const; // retourne la coordonnee a la position pos

    void set_coord(int pos, double valeur);

    Vecteur oppose() const; // oppose (additivement) le vecteur

    void trouve_valeurs(size_t& taille_max, size_t& taille_min, std::vector<double>& grand, std::vector<double>& petit, Vecteur autre) const;
    //fonction qui nous permet d'implementer l'addition / produit scalaire de deux vecteurs de dim differentes

    double norme2() const; // norme au carre

    double norme() const; // norme euclidienne

    Vecteur mod_2pi() const;

    //--------------------------------------------
    //surcharge d'operateurs

    const Vecteur operator+(Vecteur const& autre) const;

    std::ostream& affiche(std::ostream& sortie) const;//pas une surcharge d'operateur mais elle sera utilisee pour une surcharge plus tard

    const bool operator==(Vecteur const& vc) const;

    const bool operator!=(Vecteur const& vc) const;

    const Vecteur operator-(Vecteur const& autre) const;

    const Vecteur operator*(double lambda) const; // multiplication par un scalaire

    const double operator*(Vecteur autre) const; // produit scalaire


    const Vecteur operator^(Vecteur autre) const; // produit vectoriel

    const Vecteur operator~() const ;// normalise le vecteur, ie v = v / ||v|| .

    void operator+=(Vecteur const& autre);

    const void operator-=(Vecteur const& autre);

    const void operator*=(Vecteur const& autre);

    const void operator*=(double lambda);


    const void operator^=(Vecteur const& autre);
    //----------------------------------------------

};

std::ostream& operator<<(std::ostream& sortie, Vecteur v);
