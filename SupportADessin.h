#pragma once

class Systeme;
class Balle;
class Pendule;
class Brique;
class Plan;
class ObjetMobile;
class Obstacle;
class Ventilateur;

class SupportADessin {
 public:
  virtual ~SupportADessin() = default;
  // on ne copie pas les Supports
  SupportADessin(SupportADessin const&)            = delete; 
  SupportADessin& operator=(SupportADessin const&) = delete;
   // mais on peut les déplacer
  SupportADessin(SupportADessin&&)            = default; 
  SupportADessin& operator=(SupportADessin&&) = default;
  
  SupportADessin() = default; 

  virtual void dessine (const Systeme&)=0;
  virtual void dessine (const Balle&)=0;
  virtual void dessine (const Pendule&)=0;
  virtual void dessine (const Brique&)=0;
  virtual void dessine (const Plan&)=0;
  virtual void dessine (const Ventilateur&)=0;
  /* Mettre ici toutes les méthodes nécessaires pour dessiner tous les
   * objets que l'on veut dessiner
   */
};
