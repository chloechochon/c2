#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "ex_vecteur.h"
#include "constantes.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include "Systeme.h"
#include "ChampsForces.h"

class ObjetMobile: public Dessinable {
    protected:
        //attributs
        Vecteur P;
        Vecteur Pd;
        double masse;
        Vecteur force;
        double rayon;
        double temps;
        int degl;
        double alpha; //coefficient de restitution choc 
        double frottement_choc; // le coefficient μ de frottement entre corps pour chocs
        
      public:
        //Constructeur
        ObjetMobile (Vecteur param, Vecteur derparam, double m,  Vecteur F,double r, double t, int deg_ , double alp, double fchoc)
            : P (param), Pd (derparam), masse (m), force (F), rayon (r), temps (t), degl(deg_), alpha(alp), frottement_choc(fchoc) {}
            
       //destrcuteur
       virtual ~ObjetMobile() {}
            
      //  virtual double distance(const ObjetMobile& obj) = 0; // calculer distance entre objets
        
        
        ///virtual void dessine_sur(SupportADessin& support) override;

        // Methodes dans balle a l origine
    
        virtual Vecteur position () const = 0 ;
        virtual Vecteur evolution() = 0;
        virtual void agit_sur(ObjetMobile& obj) = 0;    ///A modifier pour chaque sous classe: pour obstacle: change vitesse; pour champforce: ajoute une force externe
        // ... dessine_sur();
        virtual Vecteur point_plus_proche (const ObjetMobile& obj) = 0; //calculer le point le plus proche

        double masse_vol() const;
        void ajoute_force(Vecteur  df);    ///const& ?

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
		virtual void affiche()=0;

		//pour ajouter des objets au systeme
		void ajoute_a(Systeme& S);

        //pour la covariance 
   virtual ObjetMobile* copie() const = 0;
   
    
};




class Balle : public ObjetMobile {
    public:
    // les constructeurs
    Balle (Vecteur pos, Vecteur vit,  double masse, Vecteur F, double r=1.0, double t=0.0,  int deg_=3, double alp=1, double fchoc=0)
    : ObjetMobile (pos,vit, masse, F, r, t, deg_,alp,fchoc) {}
    
    
    
    //les methodes 
    virtual Vecteur position() const override;
 
    void setposition(Vecteur a);
    
    Vecteur getvitesse() const;
    void setvitesse(Vecteur a);
    
    Vecteur evolution() override;
    virtual Vecteur point_plus_proche(const ObjetMobile& M) override;
    virtual void agit_sur(ObjetMobile& obj) override; 
	
	virtual void affiche() override;

    ///virtual void dessine_sur(SupportADessin& support) override;
    
	//methode pour la covariance
    virtual Balle* copie() const override;

    };







class Pendule : public ObjetMobile {
    public:
    //Constructeur
    Pendule (Vecteur param, Vecteur derparam, double m, Vecteur F, double r, Vecteur Or, double l, double alp=1, double fchoc=0, double t = 0, int deg_=1, double fr = 0.0)
    : ObjetMobile ( param, derparam, m, F, r, t, deg_, alp, fchoc), origine (Or), longueur (l), frottement(fr)
    {/*ajoute_force(m*g);*/ ///Cette information permettrait de mettre par defaut l action de la gravite sur le pendule
    }
    
    Pendule (Pendule const&) = default;
    /* Le theta est la seule donnée de position necessaire pour le pendule, etant donne que la longueur et l'origine sont fixes.
   
    Il y a donc un seul degre de liberte. On utilise donc P de dimension 1 (degl = 1) pour decrire la position du pendule et Pd pour sa vitesse angulaire
    */
    
    Vecteur Madirection () const;
    virtual Vecteur position() const override;
    

    
    // methodes get, necessaires pour l operateur d affichage << et pour la fonction agir_sur
    Vecteur getP() const;
    Vecteur getorigine() const;
    double getfrottement() const;
	double getlongueur() const ;
	
	virtual Vecteur evolution() override;
	
	virtual Vecteur point_plus_proche(const ObjetMobile& M) override;
    ///virtual void dessine_sur(SupportADessin& support) override;
	virtual void agit_sur(ObjetMobile& obj) override; 
	virtual void affiche() override;

    //pour la covariance
    virtual Pendule* copie() const override;
	
	

	
    private:
    //attributs     
    Vecteur origine;
    double longueur;
    double frottement;
};










