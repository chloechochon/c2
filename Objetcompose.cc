#include "Dessinable.h"
#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "ChampsForces.h"
#include "Objetcompose.h"
#include "Systeme.h"
#include <memory>

using namespace std;

 void Objetcompose::ajoute_a(Systeme& S) {
	 
	 a_ete_ajoute=true;	//On place le booléen comme true car l'objet est ajoute au systeme.
	 
	 
	 //On place chaque composante d'Objetcompose dans les tableaux du Systeme de facon séparée
	 
	 //d abord les objetsmobiles
	 for (size_t i(0); i<Obj.size(); i++){
		 S.ajoute(Obj[i]);
	}
	
	 //puis les obstacles
	 for (size_t i(0); i<Obs.size(); i++){
		 S.ajoute(Obs[i]);
	}
	
	 //puis les ChampsForces
	 for (size_t i(0); i<champsf.size(); i++){
		 S.ajoute(champsf[i]);
	}
 }
	
void Objetcompose::ajoute (ObjetMobile const& M) {	//on ajoute un objet mobile à la structure de l objet compose
	ObjetMobile* ob(M.copie());
	Obj.push_back(ob);
}
void Objetcompose::ajoute (Obstacle const& A) {		//on ajoute un obstacle
	Obstacle* ob(A.copie());
	Obs.push_back(ob);
}
void Objetcompose::ajoute (ChampForces const& C) {	//on ajoute un ChampForces
		ChampForces* ch(C.copie());
		champsf.push_back(ch);
}
//-----------------------------------------------------------------------------------------------

//methode pour un ventilateur
Obstacle* Ventilateur::getbrique() const {
	return Obs[0];				//il n y a qu une composante d obstacle (une brique) pour un ventilateur
}

ChampForces* Ventilateur::getvent() const {return champsf[0];}	//il n y a qu une composante de ChampForce (un vent) pour un ventilateur

//void Ventilateur::dessine_sur(SupportADessin& support) { support.SupportADessin::dessine(*this); }

std::ostream& operator<<(std::ostream& sortie, Ventilateur const& ventilateur){
	cout <<"voici un ventilateur" <<endl;
	(ventilateur.getvent())->affiche();
	cout << endl;
	(ventilateur.getbrique())->affiche();
	return sortie;
	}
