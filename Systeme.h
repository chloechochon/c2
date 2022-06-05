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
/*Systeme (std::vector<std::unique_ptr<ObjetMobile>>  tobj, std::vector<std::unique_ptr<Obstacle>> tobs)
    : tableau_objets(make_unique <ObjetMobile> (*tobj)), tableau_obstacles(make_unique <Obstacle> (*tobs)) {}
    
Systeme (std::vector<std::unique_ptr<ObjetMobile>>&  tobj, std::vector<std::unique_ptr<Obstacle>>& tobs)
    : tableau_objets(), tableau_obstacles() {
   for (size_t i(0); i< tobj.size(); ++i){
   tableau_objets.push_back (std::unique_ptr <ObjetMobile> (tobj[i]->copie()));
    } 
   for (size_t i(0); i< tobs.size(); ++i){
   tableau_obstacles.push_back (std::unique_ptr <Obstacle> (tobs[i]->copie()));
}
} */


~Systeme() = default;
Systeme(Systeme const&)            = default;
Systeme& operator=(Systeme const&) = default;
Systeme(Systeme&&)                 = default;
Systeme& operator=(Systeme&&)      = default;


//méthodes

virtual void dessine_sur(SupportADessin& support) override;

void evolue2(double dt, int integrateur);

//Pour pouvoir cacher les pointeurs
void ajoute(ObjetMobile* objet);
void ajoute(Obstacle* obstacle);
void ajoute(ChampForces* Champ);


void affiche() const ;
size_t taille_tab_obj () const;
size_t taille_tab_obs () const;
size_t taille_tab_champs () const;
std::unique_ptr<ObjetMobile> retour_obj (size_t i) const ;
std::unique_ptr<Obstacle> retour_obs (size_t i) const ;
std::unique_ptr<ChampForces> retour_champ (size_t i) const ;

    
/*  Inutile donc enlevé, on a trouvé d'autres moyens de faire que copier un unique_ptr
template <typename Type>
std::vector<std::unique_ptr<Type>> copie_unique(std::vector<std::unique_ptr<Type>> tableau){
	std::vector<std::unique_ptr<Type>> tab;
	for (size_t i(0); i<tableau.size();i++){
		tab.push_back (std::unique_ptr<Type> (tableau[i]->copie()));
	}
	return tab;
}
*/
    
private:
std::vector<std::unique_ptr<ObjetMobile>> tableau_objets;
std::vector<std::unique_ptr<Obstacle>> tableau_obstacles;
std::vector<std::unique_ptr<ChampForces>> tableau_champs;


};

std::ostream& operator<<(std::ostream& sortie, const Systeme& Sys);
