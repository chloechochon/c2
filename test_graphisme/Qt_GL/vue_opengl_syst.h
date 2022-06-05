#pragma once

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "SupportADessin.h"
#include "glsphere.h"
#include "ObjetMobile.h"
#include "Systeme.h"
#include "obstacle.h"
#include "Objetcompose.h"


class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
  virtual void dessine(Systeme const& a_dessiner) override;
    /*
    virtual void dessine(ObjetMobile const& a_dessiner) override;
    virtual void dessine(Obstacle const& a_dessiner) override;
    virtual void dessine(Objetcompose const& a_dessiner) override;
*/

  virtual void dessine(Balle const& a_dessiner) override;
  virtual void dessine(Pendule const& a_dessiner) override;
  virtual void dessine(Brique const& a_dessiner) override;
  virtual void dessine(Plan const& a_dessiner) override;
  virtual void dessine(Ventilateur const& a_dessiner) override;


  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);
  
  // méthode utilitaire offerte pour simplifier
  void dessineSurf (QMatrix4x4 const& point_de_vue);
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineAxe(QMatrix4x4 const& point_de_vue, QVector3D const& pos);
  void dessineSphere(QMatrix4x4 const& point_de_vue,
                     double rouge = 1.0, double vert = 1.0, double bleu = 1.0);

 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  GLSphere sphere;

  // Caméra
  QMatrix4x4 matrice_vue;
};


//Prototype de la fonction chang
void chang (QVector3D& q, Vecteur v);
