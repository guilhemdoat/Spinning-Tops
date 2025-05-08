#include "Dessinable.h"
#include "Toupie.h"
#include "Support.h"

using namespace std;






//constructeurs, destructeurs
Dessinable::Dessinable() {}

 Dessinable::Dessinable(SupportADessin* s) {
    Supp = s;
  }

Dessinable::~Dessinable() {
    delete Supp;
    Supp = nullptr;
  }




