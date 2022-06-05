#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include "ex_vecteur.h"
#include "constantes.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include "Systeme.h"
#include "ChampsForces.h"
#include "constantes.h"
#include <map>

//Ce fichier regroupe les ObjetsMobiles, les Balles et les Pendules


class ObjetMobile: public Dessinable {	//tout ObjetMobile est dessinable (mais la classe est abstraite, on ne pourra pas faire d instance
    protected:
        //attributs
        Vecteur P;	//vecteur de parametres	
        Vecteur Pd;	// derivee du vecteur de parametres
        double masse;
        Vecteur force;	//somme des forces appliquees a l objet
        double rayon;	// les ObjetsMobiles etant des objets sphériques dans ce projet, on a un rayon
        int degl;	// degre de liberte de l objet
        double alpha; //coefficient de restitution choc 
        double frottement_choc; // le coefficient μ de frottement entre corps pour chocs
        std::map<int, bool> danschamp; //Ce booléen correspond à l'information si oui ou non l'ObjetMobile est actuellement influencé par un ChampForce de numero de type int


      public:
        //Constructeur
        ObjetMobile (Vecteur param, Vecteur derparam, double m,  Vecteur F,double r, int deg_ , double alp, double fchoc)
            : P (param), Pd (derparam), masse (m), force (F), rayon (r), degl(deg_), alpha(alp), frottement_choc(fchoc) {
				
		    //On place comme force par défaut le poids et la force d'Archimède pour tous les ObjetsMobiles
		    //ATTENTION IL NE FAUT PAS INITIALISER UN OBJETMOBILE EN AJOUTANT LA FORCE DE PESANTEUR ELLE Y EST DEJA
				 Vecteur f( (m - (4*M_PI*rho_air*r*r*r)/3)*g );
				force= f+F;	
			}
            
       //destructeur
       virtual ~ObjetMobile() {}
            
	//getter et setter de danschamp
		bool getdanschamp(size_t i);
		void setdanschamp(size_t i, bool a);


        // Methodes dans balle a l origine
    
        virtual Vecteur position () const = 0 ;	//renvoie la position x y z de l objet, virtuelle pure car on la définit en fonction de la nature de l objet dans chaque sous classe
        virtual Vecteur vitesse() const = 0 ;	//renvoie vitesse vx, vy et vz
        virtual void setvitesse(Vecteur const& a) = 0 ;
        virtual Vecteur evolution() const = 0;	//renvoie l acceleration selon les forces appliquees sur l objet et les differentes contraintes exercees dessus
        void agit_sur(ObjetMobile& obj);	//pour gerer les changemets de position et de vitesse lorsqu il y a choc
//      virtual void dessine_sur(SupportADessin&) =0;
        virtual Vecteur point_plus_proche (const ObjetMobile& obj) = 0; //calcule la distance entre deux objetsMobiles

        double masse_vol() const;	//calcule la masse volumique de l objet en fonction de la masse et du rayon
        void ajoute_force(Vecteur  df);    //ajoute une force df aux forces appliquees sur l objet

	//getters et setters
        Vecteur getP() const;
        Vecteur getPd() const;
        Vecteur getforce() const;
	double getalpha() const;
	double getmasse() const;
        double getrayon() const;
        double get_temps () const;
        double getfrottement_choc() const;
        void setP (Vecteur nouv_pos);
        void setPd (Vecteur nouv_der);
        void setforce(Vecteur nouv_force);
	
	virtual void affiche() const=0;

	//pour ajouter l objet au systeme
	void ajoute_a(Systeme& S);

        //pour la covariance 
  	virtual ObjetMobile* copie() const = 0;
   
    
};
//___________________________________________________________________________________



class Balle : public ObjetMobile {	//une balle n a pas d attributs propres et ne fait que redefinir les fonctions virtuelles
    public:
    //  constructeur
    Balle (Vecteur pos, Vecteur vit,  double masse, Vecteur F, double r=0.1, int deg_=3, double alp=1, double fchoc=0)
    : ObjetMobile (pos,vit, masse, F, r, deg_,alp,fchoc) {}
    
    
    
    //les methodes 
    virtual Vecteur position() const override; 	//retourne P
    virtual Vecteur vitesse() const override;	//retourne Pd
 
    //getters et setters
    void setposition(Vecteur const& a);
    
    Vecteur getvitesse() const;
    virtual void setvitesse(Vecteur const& a) override;
    
	
    Vecteur evolution() const override;
    virtual Vecteur point_plus_proche(const ObjetMobile& M) override;
	
    virtual void affiche() const override;

    ///virtual void dessine_sur(SupportADessin& support) override;
    
    //methode pour la covariance
    virtual Balle* copie() const override;

    };


//______________________________________________________________________


class Pendule : public ObjetMobile {
    public:
    //Constructeur
    Pendule (Vecteur param, Vecteur derparam, double m, Vecteur F, double r, Vecteur Or, double l, Vecteur dir, double alp=1, double fchoc=0, int deg_=1, double fr = 0.0)
    : ObjetMobile ( param, derparam, m, F, r, deg_, alp, fchoc), origine (Or), longueur (l),  d (dir), frottement(fr)
    {	
		if (l < epsilon ) {	//un pendule ne peut pas avoir une longueur nulle ou negative, on lui donne alors une valeur par defaut
			longueur = 0.1;
			std::cout << "La longueur donnée est nulle ou négative, on la met donc par défaut à 0.1 ." <<std::endl;
		}
		
		Vecteur direction (dir);		//La direction (attention ce n est pas la direction de l axe du pendule) correspond à un vecteur orthogonal à l axe Y, pour determiner le plan dans lequel se deplace le pendule
		if((direction|g) > epsilon) {		//On teste si ce vecteur est orthogonal à l axe Y avec le vecteur g (voir les constantes)
			Vecteur y(0,1.0,0);		//Pour simplifier on définit le vecteur y selon l axe vertical des Y
          		  direction -= (!((dir|y)*y)); 
            	}
	    
		d = (!direction);	//On prend le vecteur directeur pour que la norme de d n'influence pas les calculs, on a juste besoin de la direction du vecteur

    }
    
    Pendule (Pendule const&) = default;
    
    Vecteur Madirection () const;

    /* Le theta est la seule donnée de position necessaire pour le pendule, etant donne que la longueur et l'origine sont fixes.
    Il y a donc un seul degre de liberte. On utilise donc P de dimension 1 (degl = 1) pour decrire la position du pendule et Pd pour sa vitesse angulaire
    */
    virtual Vecteur position() const override;	//on retourne la position x y z du bout du pendule en fonction de P
    virtual Vecteur vitesse() const override;	//ici en fonction de Pd
    virtual void setvitesse(Vecteur const& a) override;	//On modifie Pd selon une vitesse donnée en coordonnees cartesiennes de la vitesse au bout du pendule
    Vecteur dir() const;

    
    // methodes get, necessaires pour l operateur d affichage << et pour la fonction agir_sur
    Vecteur getP() const;
    Vecteur getorigine() const;
    double getfrottement() const;
    double getlongueur() const ;
	
    virtual Vecteur evolution() const override;	//Evolution retourne l acceleration du pendule selon les formules d oscillations
	
    virtual Vecteur point_plus_proche(const ObjetMobile& M) override;
    ///virtual void dessine_sur(SupportADessin& support) override;
    virtual void affiche() const override;

    //pour la covariance
    virtual Pendule* copie() const override;
	

    //attributs     
    private:
    Vecteur origine;	//point fixe d origine du pendule
    double longueur;	//longueur de corde du pendule
    Vecteur d;		//d correspond à un vecteur orthogonal à la verticale pour déterminer le plan dans lequel le pendule est contraint
    double frottement;  // frottements de la corde
};


std::ostream& operator<<(std::ostream& sortie, Balle const& b);		//surcharge des operateurs d affichage
std::ostream& operator<<(std::ostream& sortie, Pendule const& p);








