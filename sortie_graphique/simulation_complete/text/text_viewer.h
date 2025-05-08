#ifndef TEXT_VIEWER_H
#define TEXT_VIEWER_H

#pragma once
#include "Support.h"
#include<iostream>
#include "Systeme.h"


class TextViewer : public SupportADessin {
public:
 TextViewer(std::ostream& flot);

  virtual void dessine(Systeme const& s) override;

private:
  std::ostream& flot;

};


#endif
