#include "Dessinable.h"
#include "Toupie.h"
#include "Support.h"

using namespace std;






//Constructeurs, destructeur

Dessinable::Dessinable() {}

 Dessinable::Dessinable(SupportADessin* s) {
    Supp = s;
  }

Dessinable::~Dessinable() {
    delete Supp;
    Supp = nullptr;
  }




