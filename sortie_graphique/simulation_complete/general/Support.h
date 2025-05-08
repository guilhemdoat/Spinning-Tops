#pragma once
#include <iostream>
#include "Toupie.h"



class Systeme; //si on met #include a la place, on a une erreur "undefined reference to vtable for Systeme"
class Dessinable; //de meme ici


class SupportADessin //classe abstraite
{

 public:
  //jusqu'a present, le seul dessinable que nous utiliserons est Systeme
  virtual void dessine(Systeme const& s) = 0;

};

