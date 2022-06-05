#pragma once
#include <iostream>
#include <vector>
#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "SupportADessin.h"
#include "Dessinable.h"
#include "Systeme.h"
#include "constantes.h"

//Ce fichier regroupe les Obstacles, les Plans, les Briques
    
class Obstacle : public Dessinable {
    public:    
    // Constructeur
    Obstacle(Vecteur ori)
     : obs_origine(ori) {}
    
    //destructeur
    virtual ~Obstacle() {}
    
    Vecteur getobs_origine() const;
   
    
    virtual Vecteur point_plus_proche(const ObjetMobile& M) = 0;	//pour determiner quel est le point appartenant a l obstacle duquel l objet mobile est le plus proche
    virtual double distance(const ObjetMobile&) =0;		//determiner la distance entre l objet et l obstacle
    void agit_sur(ObjetMobile& obj);				//pour gerer les chocs
    virtual void affiche() =0;

    ///virtual void dessine_sur(SupportADessin& support) = 0;
	
    //pour la covariance
    virtual Obstacle* copie() const = 0;

    void ajoute_a(Systeme& S);

	
    protected:
    Vecteur obs_origine;		//Un obstacle a une origine comme unique attribut
    
};



class Plan :public Obstacle {
    public:
    //constructeur 
    Plan (Vecteur ori, Vecteur di1, Vecteur di2)
    : Obstacle(ori), dir1(di1), dir2(di2){}
    
    Vecteur point_plus_proche(const ObjetMobile& M);
    Vecteur n() const;			//pour determiner le vecteur normal au plan
    virtual void affiche() override;
    virtual double distance(const ObjetMobile&) override; //distance de l'ObjetMobile par rapport au plan


    ///virtual void dessine_sur(SupportADessin& support) override;
    
    //pour la covariance
    virtual Plan* copie() const override;

    private:
    Vecteur dir1;	//Un plan est defini par deux vecteurs non colineaires et un point (l origine heritee d obstacle)
    Vecteur dir2;
    
};

ostream& operator<<(ostream& sortie, Plan& P);

class Brique : public Obstacle {
	public:
    //constructeur
    Brique (Vecteur ori, Vecteur lon, Vecteur lar, double haut) : Obstacle(ori), longueur(lon), largeur(lar), hauteur(haut) {
        Vecteur a(!longueur); //a prend seulement la direction de longueur
        Vecteur b(!largeur); //b prend seulement la direction de largeur
        if((b|a) > epsilon) {
            largeur = largeur - (largeur|a)*a;	 //il faut que les deux vecteurs soient orthogonaux et on modifie largeur en consequence
            }
        }                                   
        
    //methodes
    Vecteur getlongueur() const;
    Vecteur getlargeur() const;
    double gethauteur() const;
   
    Vecteur point_plus_proche(const ObjetMobile& M) override;	//point appartenant a la brique dont l objet est le plus proche
    Vecteur n() const;
    virtual void affiche() override;
    virtual double distance(const ObjetMobile&) override;	//distance de l'ObjetMobile par rapport à une brique


///	virtual void dessine_sur(SupportADessin& support) override;

	//pour la covariance
    virtual Brique* copie() const override;

  
    
    private:
    // de plus il herite d'une origine par Obstacle
    Vecteur longueur;
    Vecteur largeur;
    double hauteur;	//hauteur a pour direction le vecteur normal n obtenu par la methode n()
};

ostream& operator<<(ostream& sortie, Brique& B);

Vecteur point_portion (ObjetMobile const& M, Vecteur dir1, Vecteur dir2, Vecteur point); 
// permet d utiliser la fonction point_plus_proche de plan dans la methode de Brique,
// en modelisant un plan a partir de vecteurs directeurs de chaque face de Brique.
