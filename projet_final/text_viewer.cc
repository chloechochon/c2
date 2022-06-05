#include <iostream> // pour endl
#include "text_viewer.h"
#include "Systeme.h"
#include "ObjetMobile.h"
#include "obstacle.h"
#include "SupportADessin.h"
#include "Objetcompose.h"
#include "ChampsForces.h"


using namespace std;

void TextViewer::dessine(Systeme const& a_dessiner)
{
    /// est ce que la surcharge de << faite sur la classe Systeme est suffisante pour l'affichage?
  flot << a_dessiner << endl;
}

void TextViewer::dessine(Balle const& a_dessiner){
    flot << a_dessiner << endl;
}
void TextViewer::dessine(Pendule const& a_dessiner){
     flot << a_dessiner << endl;
}
void TextViewer::dessine(Brique const& a_dessiner){
     flot << a_dessiner << endl;
}
void TextViewer::dessine(Plan const& a_dessiner){
     flot << a_dessiner << endl;
}
/*
void TextViewer::dessine(Ventilateur const& a_dessiner){
     flot << a_dessiner << endl;
}*/
