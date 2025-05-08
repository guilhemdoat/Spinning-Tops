#pragma once
#include <iostream>
#include "Toupie.h"
#include "ConeSimple.h"
//#include "Dessinable.h"


//class Toupie;
//class ConeSimple;
class Systeme;
class Dessinable;


class SupportADessin
{

 public:
  //virtual ~SupportADessin();
  // on supposera ici que les supports ne sont ni copiés ni déplacés



  virtual void dessine(Systeme const& s) = 0;

};

