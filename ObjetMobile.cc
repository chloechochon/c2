#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "constantes.h"
#include "SupportADessin.h"
#include "Systeme.h"
#include "ChampsForces.h"
using namespace std;


// Ce document sert a definir les methodes propres a tous les objets mobiles de facon generale


//ObjetMobile
//Methodes
 double ObjetMobile::masse_vol() const {return (masse/(((4*M_PI)/3)*carre(rayon)*rayon)); }	//calcul de la masse volumique
    
 void ObjetMobile::ajoute_force(Vecteur  df){    //const&
        force+=df;}

double ObjetMobile::getmasse() const {return masse;}
double ObjetMobile::getrayon() const {return rayon;}
Vecteur ObjetMobile::getPd() const{return Pd;}
Vecteur ObjetMobile::getP() const {return P;};
Vecteur ObjetMobile::getforce() const{return force;}
double ObjetMobile::getalpha() const {return alpha;}				//utile pour agit_sur() des Obstacles
double ObjetMobile::getfrottement_choc() const {return frottement_choc;}	//utile pour agit_sur() des Obstacles


void ObjetMobile::setP (Vecteur nouv_pos){ P=nouv_pos; }
void ObjetMobile::setPd (Vecteur nouv_der){ Pd=nouv_der;}
void ObjetMobile::setforce(Vecteur nouv_force){force=nouv_force;}

bool ObjetMobile::getdanschamp(size_t i){ return danschamp.at(i);}
void ObjetMobile::setdanschamp(size_t i, bool a){ danschamp[i] = a;}


void ObjetMobile::ajoute_a(Systeme& S){
	S.ajoute(this);				//Pour ajouter l objet au systeme de facon polymorphique (le mettre dans le bon tableau en attribut du systeme
	cout << "un objet mobile est ajouté au systeme"<<endl;
	 }  

void ObjetMobile::agit_sur(ObjetMobile& obj){  
		//soit l'objet 2 celui passé en parametre
	
		
		if (((position()-obj.position()).norme()) - (rayon+obj.getrayon()) < epsilon) { //verification qu'il y ait bien un choc 
            		Vecteur normal(!(position()-obj.position()));			//vecteur (unitaire) normal au point de choc
			
			double Fn1 (force|normal);
			Vecteur a(obj.getforce());
			double Fn2(a|normal);

			if (Fn1 < epsilon) {
				force-=(Fn1*normal); 
                		obj.setforce(obj.getforce()+(Fn1*normal));
			}
			
			if (Fn2 > epsilon) {
				force+=(Fn2*normal); 
                obj.setforce(obj.getforce()-(Fn2*normal));
			}
			//valeur necessaire au calcul de la vitesse relative du point de contact
			double lambda ( (1+alpha)*(obj.getmasse()/(masse+obj.getmasse())));
			
			//calcul vitesse relative du point de contact
			double v_etoile((obj.vitesse()-vitesse())|normal);
			Vecteur v_contact((vitesse()-obj.vitesse())+(v_etoile*normal));
            Vecteur delta_v;
            double condition(7*frottement_choc*(1+alpha)*v_etoile);
            if (condition - (2*v_contact.norme()) > epsilon){
                delta_v=( (lambda*v_etoile)*normal-((2*obj.getmasse()/(7*(masse+obj.getmasse())))*v_contact));
			}else if (v_contact.norme()!=0){
                    delta_v=lambda*v_etoile*(normal-frottement_choc*(!v_contact));
                    }
			//mise à jour des vitesses
			setvitesse(vitesse()+delta_v);
			obj.setvitesse(obj.vitesse()-(masse/obj.getmasse())*delta_v);
             
             //affichage
             cout <<"calcul:"<<endl;
             cout<<"n= "<<normal<<endl;
             cout<<"lambda :"<<	lambda<<endl;
             cout<<"Fn1"<<Fn1<<endl;
             cout<<"Fn2"<<Fn2<<endl;
             cout <<"vstar= "<<v_etoile<<endl;
             cout <<"vc= "<<v_contact<<endl;
             cout <<"7 mu (1+alpha) vstar "<< condition<<endl;
             cout <<"2*vc.norme()"<<2*v_contact.norme()<<endl;
             cout <<"dv: "<<delta_v<<endl;
             
             cout<<endl;
             cout <<"apres choc : :"<<endl;
             cout<<"vitesse objet1= "<<Pd <<endl;
             cout << "vitesse objet2= "<< obj.getPd() <<endl;
             cout <<"force objet1 "<< force<<endl;
             cout<<"force objet2 "<<obj.getforce()<<endl;
	}
}                           

	



//_______________________________________________________________________________________________

//Balle
    //les methodes : Balle
    Vecteur Balle::position() const {return P;}
    Vecteur Balle::vitesse() const {return Pd;}

    void Balle::setposition (Vecteur const& a) { P = a;}
        
    Vecteur Balle::getvitesse() const {return Pd;}
    void Balle::setvitesse (Vecteur const& a) { Pd = a;}
    
    Vecteur Balle::evolution() const {
			Vecteur Pdd; //derivée seconde de la position 
			Pdd=(1/masse)*force;
			return Pdd;
	}
	
	Vecteur Balle::point_plus_proche(const ObjetMobile& M){
		Vecteur point_proche(M.position()-P);
		return point_proche;
	}
	
	
///void Balle::dessine_sur(SupportADessin& support) { support.dessine(*this); }



Balle* Balle::copie() const { //pour pouvoir utiliser la methode copieobjet
        return (new Balle(*this));}



	
	
// Les operateurs d affichage
void Balle::affiche() const{
    cout << "La balle est constituée de :" << endl;
    cout << position();
    cout << "  #position"<<endl;
    cout <<Pd;
    cout << "  #vitesse" <<endl;
    cout << masse;
    cout << "  #masse" << endl;
    cout << masse_vol();
    cout << "  #masse volumique "<<endl;
    cout << rayon;
    cout << "  #rayon" << endl;
    cout << force;
    cout <<" #force" <<endl;
    cout << endl;
    cout << evolution() << " #accélération";
    cout << endl;
    }
  

std::ostream& operator<<(std::ostream& sortie, Balle const& b){
	b.affiche();
	return sortie;
	}

//____________________________________________________________
//Pendule

//Methodes
Vecteur Pendule::getP() const{return P;}
Vecteur Pendule::getorigine()const {return origine;}
double Pendule::getlongueur() const {return longueur;}

Vecteur Pendule::Madirection() const {
    Vecteur dir (position()-origine);
    return (!dir);
}
    
Vecteur Pendule::position() const { //direction de l'axe
	Vecteur Y (0,1,0);
	Vecteur y (-cos(P.getcomposante(0)) * Y);
	Vecteur xplan (sin(P.getcomposante(0)) * (!d));
    Vecteur laposition (longueur*(xplan+y));
    laposition += origine;
    return laposition;
    }
//Vitesse du bout du pendule
Vecteur Pendule::vitesse() const {
	Vecteur Y (0,1,0);
	Vecteur vx ( (longueur* cos(P.norme()) * Pd.norme()) * (!d));
	Vecteur vy (longueur*sin(P.norme())*Pd.norme()*Y);
	Vecteur v (vx + vy);
	return v;
}
void Pendule::setvitesse(Vecteur const& vit) {
	Vecteur thetapoint (vit.norme()/longueur);
	Pd = thetapoint;
}
	
	

Vecteur Pendule::point_plus_proche(const ObjetMobile& M){
		Vecteur point_proche(M.position()-position());
		return point_proche;
	}


Vecteur Pendule::evolution() const {
	double sin_P (sin (P.getcomposante(0)));
	double cos_P (cos (P.getcomposante(0)));
	cout <<"sin_P " <<sin_P <<"  cos_P "<<cos_P<<endl;
	//On definit le plan dans lequel est restreint le pendule: la verticale et d
	Vecteur bas(0.0,-1.0,0.0);
	
	double inv_ml (1/(masse*longueur));
	double acc ( (cos_P * (force|d)) - (sin_P * (force|bas)) - ((frottement/longueur)*Pd.getcomposante(0)) );
	cout << "acceleration " << acc << endl;

	Vecteur Pdd (acc*inv_ml);
	cout <<" evolution "<<Pdd << endl; 
	return  Pdd; } 

/// void Pendule::dessine_sur(SupportADessin& support){ support.dessine(*this); }

Pendule* Pendule::copie() const { //pour pouvoir utiliser la methode copieobjet
        return (new Pendule(*this));
        }





//operateur
void Pendule::affiche() const{
    cout << "Le pendule a pour caractéristiques: " << endl;
    cout << masse << "  #masse du pendule" << endl;
    cout <<longueur;
    cout << "   #longueur du pendule" << endl;
    cout <<origine;
    cout << "  #origine du pendule" << endl;
    cout << position() << "  #position au bout du pendule" << endl;
    cout << Madirection() << "  #direction du pendule" << endl;
    cout << P;
    cout << "   #theta du pendule"<<endl;
    cout << Pd;
    cout << "   #theta point du pendule" <<endl;
    cout << force;
    cout <<"  #force appliquée sur le pendule" <<endl;
    cout << frottement;
    cout << "  #frottement du pendule" << endl;
    cout << endl;
  }

std::ostream& operator<<(std::ostream& sortie, Pendule const& p){
	p.affiche();
	return sortie;
}




