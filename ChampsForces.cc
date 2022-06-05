#include "ObjetMobile.h"
#include "ex_vecteur.h"
#include "ChampsForces.h"
#include "Systeme.h"
#include <cmath>
#include <iostream>
#include <map>
using namespace std;

//----------------------------------------------------------------------------------------------------------------
//pour ChampForces

    //Methodes
Vecteur ChampForces::getintensite() const {return intensite;}

void ChampForces::ajoute_a(Systeme& S){
	S.ajoute(this); //  pour pouvoir ajouter un ChampForces  a un Systeme , le plus simple c'est d'appeler une methode propre au Systeme qui ajoutera ce ChampForces au bon endroit 
	cout <<"un Champ de force a ete ajoute au systeme"<<endl;
	}
	
int ChampForces::compteur(0); 	//on initialise le compteur à 0
int ChampForces::getnumero() const { return numero; }


	

//--------------------------------------------------------------------------------------------------------------
//pour Vent

	//methodes
 Vecteur Vent::getnormale() {return n;}	//renvoie la direction direction du vent, l attribut n
 
 Vent* Vent::copie() const { 
        return (new Vent(*this));}
 
 bool Vent::influe(ObjetMobile const& obj) const{ 	 //On verifie que l'objet se trouve ou non dans le champ d'action du vent

	 //Vecteur distance entre l'objet et l'origine
	 Vecteur dist (obj.position() - origine);
	 
		if ((  (largeur.norme()- (dist|(!largeur))) > epsilon) and ( (hauteur.norme()- (dist|(!hauteur))) > epsilon ) and ((profondeur- (dist|n)) > epsilon) and ((dist|n)> epsilon) and ((dist|(!largeur))> epsilon) and ((dist|(!hauteur))>epsilon) ){
			return true;
		}
		else {return false;}
 }
 
//Si l objet est dans le rayon d'action (== la fonction influe() renvoie true), l'ObjetMobile a sa trajectoire impactée par le ChampForce
 void Vent::agit_sur(ObjetMobile& obj) const {
	 
	 //Force appliquée par le vent selon son intensite et le volume de la sphère obj
	 Vecteur F;
	 F = (3.77*obj.getrayon()*obj.getrayon()*intensite.norme()*intensite.norme())*n;	//on suit la formule donée dans le complement mathématique du projet
	
	 //L objet etait il deja dans le rayon d action du champ?
	 bool a(obj.getdanschamp(this->getnumero()));
	 
	 if ( (influe (obj)) and (not a)){ 	//si l objet rentre dans le champ:
		 // l'objet est dans le champ (influe() renvoie true) et la force du champ n'a pas deja été ajoutée alors :
		 obj.setdanschamp(this->getnumero(), true); //dire pour la suite dans le booleen que le champ a deja été ajouté aux forces sur l'objet
		 obj.setforce (obj.getforce()+F); //ajouter la force du Vent à celles de l objet
	 }
	 else if ( (not influe(obj)) and (a)){	//Si l'objet est sorti du champ (c est a dire que influe retourne false et le booleen affiche true)
		 obj.setdanschamp(this->getnumero(), false);
		 obj.setforce (obj.getforce() - F);
	 }
	 //Si en revanche l objet n est pas dans le champ et ne l etait pas de base ou si il est dans le champ mais l etait deja avant, il ne se passe rien
 }

 void Vent::affiche() const {
	cout << "Ce Vent a pour caractéristiques: "<<endl;
	cout << "intensité: " << intensite << endl;
	cout << "origine : " << origine << endl;
	cout << "direction du vent n : " << n << endl;
	cout << "hauteur : " << hauteur << endl;
	cout << " largeur : " << largeur << endl;
	cout << "profondeur : " << profondeur << endl;

	
   }
//On surcharge l operateur << pour le Vent à l aide de la fonction affiche()
ostream& operator<<(ostream& sortie, Vent const& vent){
    vent.affiche();
    return sortie;
    }
