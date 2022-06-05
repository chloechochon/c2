#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Dessinable.h"
#include "ObjetMobile.h"
#include "ChampsForces.h"
#include "ex_vecteur.h"
#include "obstacle.h"


class Objetcompose : public Dessinable {
	public:
	//constructeur 
	Objetcompose() { a_ete_ajoute=false;}
	Objetcompose (ObjetMobile& A, Obstacle& B, ChampForces& C) : Obj(), Obs (), champsf () { ajoute(A); ajoute(B); ajoute(C); a_ete_ajoute=false;} 
	Objetcompose (ObjetMobile& A, Obstacle& B) : Obj(), Obs (), champsf () { ajoute(A);  ajoute(B); a_ete_ajoute=false;} 
	Objetcompose (Obstacle& B, ChampForces& C) : Obj(), Obs (), champsf () { ajoute(B);  ajoute(C); a_ete_ajoute=false;}
	Objetcompose (ObjetMobile& A, ChampForces& C) : Obj(), Obs (), champsf () { ajoute(A);  ajoute(C); a_ete_ajoute=false;} 
	
	//Destructeur si la methode ajoute a (qui les detruit car elle a la priorité (c'est des unique ptr donc ils sont detruits)) n'a pas été utilié
	~Objetcompose() {
		
		//pour les objets mobiles:
		if (a_ete_ajoute){
			for (size_t i(0); i<Obj.size(); i++) {
				delete Obj[i];
				std::cout <<"les objet mobiles ont ete detruit"<<std::endl;}
			}
			
		//pour les obstacles:
		if (a_ete_ajoute){
			for (size_t i(0); i<Obs.size(); i++) {
				delete Obs[i];
				std::cout <<"les obstacles ont ete detruit"<< std::endl;}
			}
			
		 //pour les chammps de force
		if (a_ete_ajoute){
			for (size_t i(0); i<champsf.size(); i++) {
				delete champsf[i];
				std::cout <<"les champs de force ont ete detruits"<<std::endl;}
			}
			
		 
		 };
		 
	
 

	void ajoute (ObjetMobile const&);	//ajoute un objetmobile (en le mettant sous forme de pointeur) au tableau Obj
	void ajoute (Obstacle const&);		//ajoute un Obstacle au tableau Obs
	void ajoute (ChampForces const&);	//ajoute un ChampForces au tableau des champsf
	
	//methodes 
	void ajoute_a(Systeme& S);		
	//virtual void dessine_sur (SupportADessin& ) = 0;
	
	protected:
	std::vector<ObjetMobile*> Obj;
	std::vector<Obstacle*> Obs;
	std::vector<ChampForces*> champsf;
	bool a_ete_ajoute; 			//pour savoir si l'objet composé a été ajouté au systeme 
};


class Ventilateur : public Objetcompose  {
	
	public:
	Ventilateur (Brique bri, Vent v) : Objetcompose(bri,v) {}	//On force la construction du Ventilateur à avoir uniquement une brique et un vent

	// virtual void dessine_sur(SupportADessin& support) override;
	Obstacle* getbrique() const;
	ChampForces* getvent() const;
		
};

std::ostream& operator<<(std::ostream& sortie, Ventilateur const& ventilateur);

