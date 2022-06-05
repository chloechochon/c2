#pragma once
#include "ex_vecteur.h"
#include "Systeme.h"
#include "constantes.h"
#include <iostream>

//Afin d'éviter l inclusion circulaire on prototype les classes ObjetMobile et Systeme
class ObjetMobile;
class Systeme;

class ChampForces {
    public:
	//Constructeur de ChampForces: un ChampForces est constitue
	ChampForces (Vecteur F)
		: intensite (F) {
			numero = compteur; // l'explication de cette partie est dans les attributs
			++compteur;
			}
	
	// si on fait une copie on crée quand meme un champ de force donc le compteur doit augmenter (voir explication dans attributs)
	ChampForces (ChampForces const& C) {
		 ++ compteur;
		 numero = compteur; 
		 intensite= C.getintensite();
		  }
	
	// afin de faciliter l'utilisation du compteur on supprimer la capacité d'utiliser l'opérateur d affectation =
	//(on aurait pu faire de la meme facon que pour le constructeur de copie mais ici cet operateur n est pas utilise alors c est inutile
	ChampForces& operator=(ChampForces const& ) = delete;
	
	//Destructeur : on garde le destructeur par défaut, placé en virtuel pour le transmettre aux sous-classes
	virtual ~ChampForces() {}
	
	
	//methodes 
    void ajoute_a(Systeme& S); //pour ajouter un champ de force a un systeme 
    virtual void agit_sur(ObjetMobile& obj) const =0; //On ne va pas créer d'instance de ChampForces, c'est une classe abstraite. En efet excepte la pesanteur et le force d'Archimede il n'y a pas de champ qui s'applique de facon délocalisée générale
    Vecteur getintensite() const; 	//retourne l intensite du ChampForce
    virtual ChampForces* copie() const =0; //utile pour pouvoir faire des copies profondes polymorphiques
    virtual int getnumero() const =0;	//retourne le numero propre au ChampForce
    virtual void affiche() const =0;

    protected:
    //les attributs
    Vecteur intensite;
	
	//On crée un attribut de classe nommé compteur.
    //le compteur permet de donner un numéro à chaque instance ChampForce créée pour se retrouver dans la map de danschamp et déterminer quel champ influence ou non l'objet
   	static int compteur;
	int numero;
};




class Vent : public ChampForces {
	public:
	Vent (Vecteur inten,Vecteur orin, Vecteur l, Vecteur hau, double pro)
	: ChampForces(inten), origine(orin), largeur(l), hauteur(hau), profondeur(pro) { 
				
		n = (!intensite);	//n est le vecteur normal de la direction du vent, qui est donnée par le vecteur intensite
		
		//au cas ou les vecteurs ne soient pas perpendiculaires, on les rend perpendiculaires entre eux (ex: largeur doit etre perpendiculaire a n)
		if ((largeur|n) > epsilon) {
			largeur= largeur - (largeur|n)*n;
		}	
		
		if ((hauteur|n) > epsilon) {
			hauteur= hauteur - (hauteur|n)*n;
		}
		
		if ((largeur|hauteur) > epsilon) { 
			 Vecteur a(!largeur);
			hauteur = hauteur - (hauteur|a)*a;
		}
		
	}
	//methode 
	Vecteur getnormale(); // renvoie la direction du vent
	virtual Vent* copie() const override; //utile pour pouvoir faire des copies profondes polymorphiques
	virtual void agit_sur(ObjetMobile& obj) const override; //si il y a besoin on rajoute l'intensite du vent aux forces de l'objet (on a par exemple pas besoin de rajouter deux fois un vent si l'objet s'est juste deplace dans le vent) 
	bool influe (ObjetMobile const& obj) const; //pour verifier si l'objet est dans le champ
	virtual void affiche() const override; 
	virtual int getnumero() const override;

	private:
	Vecteur origine;
	Vecteur n; //direction du vent 
	Vecteur largeur;
	Vecteur hauteur;
	double profondeur;
	};
	
std::ostream& operator<<(std::ostream& sortie, Vent const& vent); // utilise les fonctions affiche()
