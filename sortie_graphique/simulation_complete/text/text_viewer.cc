#include<iostream>

#include"Support.h"
#include "Dessinable.h"
#include "text_viewer.h"


using namespace std;
TextViewer::TextViewer(ostream& flot)
    : flot(flot) {}

 void TextViewer::dessine(Systeme const& s) {
    s.affiche_court(cout);
}
