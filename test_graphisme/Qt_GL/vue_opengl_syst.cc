#include "vue_opengl_syst.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "obstacle.h"
#include "Systeme.h"
#include "ObjetMobile.h"
#include "ChampsForces.h"
#include "Objetcompose.h"
#include "SupportADessin.h"
#include <QMatrix4x4>

using namespace std;

void chang (QVector3D& q, Vecteur v){
    if (v.taille()==3){
    q.setX (v.getcomposante(0));
    q.setY (v.getcomposante(1));
    q.setZ(v.getcomposante(2));
    }else{
        cout << "une erreur dans la taille du vecteur"<< endl;
    }
}

// ======================================================================
void VueOpenGL::dessine(Systeme const& a_dessiner)
{
    for (size_t i(0); i < a_dessiner.taille_tab_obj(); ++ i){
       (*(a_dessiner.retour_obj(i))).dessine_sur(*this);
    }
    for (size_t i(0); i < a_dessiner.taille_tab_obs(); ++ i){
        (*(a_dessiner.retour_obs(i))).dessine_sur(*this);
    }
    //On ne peut pas dessiner un ChampForce donc fini!

}

//=========

void VueOpenGL::dessine(Brique const& a_dessiner)
{
  QMatrix4x4 matrice;
  matrice.setToIdentity();

  // les arguments propres a la fonction translate sont trois éléments float
  QVector3D pos;
  chang(pos, a_dessiner.getobs_origine());
  matrice.translate(pos);

  //Plutôt que modifier les dimensions dans la fonction dessineCube, on modifie les dimensions de l'unité 1 sur chaque axe du repère de la matrice
  matrice.scale(a_dessiner.getlongueur().norme(), a_dessiner.getlargeur().norme(), a_dessiner.gethauteur());

 ///matrice.rotate(45.0, 0.0, 1.0, 0.0);   //Pas necessaire?

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // repasse en mode "plein"

  dessineCube(matrice);
}
//=========
void VueOpenGL::dessine(Balle const& a_dessiner)
{
 // Q_UNUSED(a_dessiner); // dans cet exemple simple on n'utilise pas le paramètre
  QMatrix4x4 matrice;

  //On place le point de départ à l'origine
  matrice.setToIdentity();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // repasse en mode "plein"

  QVector3D pos;
  chang(pos, a_dessiner.getP());
  matrice.translate(pos);
  matrice.scale(a_dessiner.getrayon());
  dessineSphere(matrice, 0.0, 0.0, 1); // bleu
}


//=========
void VueOpenGL::dessine(Plan const& a_dessiner){
    QMatrix4x4 matrice;
    //On place le point de départ à l'origine
    matrice.setToIdentity();
    
    //On décale l'origine de la matrice au point d'origine du plan
    QVector3D pos;
    chang(pos, a_dessiner.getobs_origine());
    matrice.translate(pos);
    
    QVector3D normale;
    chang(normale, a_dessiner.n());
    QVector3D y (0.0f,1.0f,0.0f);
    //On pose l'orientation du plan:
    //la position d'un point du plan, la normale au plan, ainsi que le vecteur y déterminant le haut
    matrice.lookAt(pos, normale, y);
    
    //Pour dessiner un plan on dessine simplement une grande surface
    dessineSurf(matrice);
}

//==========
void VueOpenGL::dessine(Pendule const& a_dessiner){
    //On commence par dessiner le fil du pendule, soit un axe mobile à une extrémité
    QMatrix4x4 matr_axe;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"

    matr_axe.setToIdentity();       //On se place au centre du repère
    QVector3D ori;
    chang(ori, a_dessiner.getorigine());
    matr_axe.translate(ori);        //On se place à l'origine d'ancrage du pendule
    matr_axe.scale(a_dessiner.getlongueur());   // On détermine la longueur 1 comme la longueur de corde du pendule
    QVector3D pos;
    chang(pos, a_dessiner.Madirection());
    dessineAxe (matr_axe, pos);

    QMatrix4x4 matr_sphere;
    QVector3D pos2;
    chang(pos2, a_dessiner.position());
    matr_sphere.translate(pos2);
    matr_sphere.scale(a_dessiner.getrayon());
    dessineSphere(matr_sphere, 0.0, 0.0, 1); // bleu

}

void VueOpenGL::dessine(Ventilateur const& a_dessiner){
    a_dessiner.getbrique()->dessine_sur(*this);
}




// ======================================================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, 0.0, -4.0);
  matrice_vue.rotate(60.0, 0.0, 1.0, 0.0);
  matrice_vue.rotate(45.0, 0.0, 0.0, 1.0);
}













// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}




















//=======================================================================
//Cette fonction sert à dessiner une surface (principalement pour le plan) carrée très grande
void VueOpenGL::dessineSurf (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  GLfloat a (200);
  glBegin(GL_QUADS);
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, +a, 0.0, -a);
  prog.setAttributeValue(SommetId, +a, 0.0, +a);
  prog.setAttributeValue(SommetId, -a, 0.0, +a);
  prog.setAttributeValue(SommetId, -a, 0.0, -a);

  glEnd();
}

// ======================================================================
void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}
//======================================================================
void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue,
                               double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}

// ======================================================================
void VueOpenGL::dessineAxe (QMatrix4x4 const& point_de_vue, QVector3D const& pos)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_LINES);

  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);

  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, pos);


  glEnd();
}
