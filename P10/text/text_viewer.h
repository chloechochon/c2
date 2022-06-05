#pragma once

#include <iostream>
#include "SupportADessin.h"
#include "ObjetMobile.h"
#include "obstacle.h"
#include "Objetcompose.h"

class TextViewer : public SupportADessin {
public:
 TextViewer(std::ostream& flot)
    : flot(flot)
  {}
  virtual ~TextViewer() = default;
  // on ne copie pas les TextViewer
  TextViewer(TextViewer const&)            = delete; 
  TextViewer& operator=(TextViewer const&) = delete;
   // mais on peut les déplacer
  TextViewer(TextViewer&&)            = default; 
  TextViewer& operator=(TextViewer&&) = default;

  virtual void dessine(Systeme const& a_dessiner) override;
  virtual void dessine(Balle const& a_dessiner) override;
  virtual void dessine(Pendule const& a_dessiner) override;
  virtual void dessine(Brique const& a_dessiner) override;
  virtual void dessine(Plan const& a_dessiner) override;
  virtual void dessine(Ventilateur const& a_dessiner) override;

private:
  std::ostream& flot;
};
