#pragma once
#include "Dessinable.h"
#include <vector>
#include <memory>
class ChampForces;
class Objetcompose;
class Obstacle;
class ObjetMobile;

class Systeme :public Dessinable {
public:
//constructeur
Systeme() = default;

~Systeme() = default;
Systeme(Systeme const&)            = default;
Systeme& operator=(Systeme const&) = default;
Systeme(Systeme&&)                 = default;
Systeme& operator=(Systeme&&)      = default;


//méthodes

virtual void dessine_sur(SupportADessin& support) override;

void evolue2(double dt, int integrateur);	//La fonction evolue2 correspond a l evolution de tout le systeme, en prenant en compte les interactions de chaque objet et ChampsForces.
//L argument 'int integrateur' permet de determiner quel integrateur utiliser dans l evolution: pour l'entier de valeur 1 recue, c est l integrateur Newmark qui est choisi, et le 2 correspond à EulerCromer
//Plutot qu utiliser un booleen on prend un int pour permettre d utiliser plus d integrateurs que 2 si besoin (si on en rajoutait)

//Pour pouvoir ajouter les elements dans les tableaux selon leur type, en faisant appel a une methode polymorphique:
void ajoute(ObjetMobile* objet);
void ajoute(Obstacle* obstacle);
void ajoute(ChampForces* Champ);


void affiche() const ;
size_t taille_tab_obj () const;									//retourne la taille du tableau des objets
size_t taille_tab_obs () const;									//retourne la taille du tableau des obstacles
size_t taille_tab_champs () const;								//retourne la taille du tableau des champs
std::unique_ptr<ObjetMobile> retour_obj (size_t i) const ;		//retourne le ième element du tableau d objets
std::unique_ptr<Obstacle> retour_obs (size_t i) const ;			//retourne le ième element du tableau d obstacles
std::unique_ptr<ChampForces> retour_champ (size_t i) const ;	//retourne le ième element du tableau de ChampsForces

    
private:
std::vector<std::unique_ptr<ObjetMobile>> tableau_objets;		//les elements sont classés selon leur type dans trois tableaux differents
std::vector<std::unique_ptr<Obstacle>> tableau_obstacles;
std::vector<std::unique_ptr<ChampForces>> tableau_champs;


};

std::ostream& operator<<(std::ostream& sortie, const Systeme& Sys);
