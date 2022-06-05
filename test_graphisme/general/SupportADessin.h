#pragma once

//Pour casser la dependance cyclique on fait un prototypage des differentes classes utilisees plutot que faire un lien avec les fichiers sources
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

};
