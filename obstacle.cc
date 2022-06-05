#include <iostream>
#include <array>
#include <vector>
#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "obstacle.h"
#include "SupportADessin.h"
#include "Systeme.h"
#include "constantes.h"

using namespace std;


//methodes obstacle
	Vecteur Obstacle::getobs_origine() const { return obs_origine;}


    double Plan::distance(const ObjetMobile& M){
        Vecteur dist (Plan::point_plus_proche(M) - M.position());
        double distance ( dist.norme() - M.getrayon());
        return distance;
    }
    double Brique::distance(const ObjetMobile& M){
        Vecteur dist (Brique::point_plus_proche(M) - M.position());
        double distance ( dist.norme() - M.getrayon());
        return distance;
    }
    
    void Obstacle::agit_sur(ObjetMobile& obj){	//Pour gerer les chocs avec un ObjetMobile, les plans et briques fonctionnent de la meme facon (voir le complement mathematique pour les calculs)
		
		//verification qu'il y ait bien un choc 
		if (distance(obj) < epsilon) {
			//mise à jour les forces s’exerçant sur l'objet
           		Vecteur testnormal(!(obj.position()-point_plus_proche(obj)));//vecteur (unitaire) normal au point de choc
			cout << "normal: " << testnormal <<endl;
			Vecteur normal;
			if (testnormal.getcomposante(2)>=0.0) { normal=testnormal;} else { normal=-testnormal;}
			
			
			Vecteur a(obj.getforce());
			double Fn1(a|normal);

			if (Fn1<epsilon) {
				obj.getforce()-=(Fn1*normal); 
			} ///pourquoi on ne fait pas quand Fn1 est positif ?

			//calcul vitesse relative du point de contact
			double v_etoile(-obj.vitesse()|normal);
			Vecteur v_contact((obj.vitesse())+(v_etoile*normal));
         		Vecteur delta_v;

          		double condition(7*obj.getfrottement_choc()*(1+obj.getalpha())*v_etoile);
            		if (condition - 2*v_contact.norme() > epsilon){
				delta_v= (((1+obj.getalpha())*v_etoile)*normal) - (2/7)*v_contact;

			} 
			else{

              			delta_v=(1+obj.getalpha())*v_etoile*(normal- (obj.getfrottement_choc()*(!v_contact)));
                		cout << "v_contact" << v_contact <<endl;
                		cout << "!v_contact : " << !v_contact<< "delta_v" <<endl;
			}

		obj.setvitesse(obj.vitesse()+delta_v);

		//affichage
		cout <<"calcul:"<<endl;
                cout <<"vstar= "<<v_etoile<<endl;
             	cout <<"vc= "<<v_contact<<endl;
             	cout <<"7 mu (1+alpha) vstar"<< condition<<endl;
             	cout <<"dv"<<delta_v<<endl;
             	cout<<endl;
             
		cout <<"apres rebond au sol : :"<<endl;
             	cout << "vitesse balle= "<< obj.getPd() <<endl;
             	cout<<"force balle "<<obj.getforce()<<endl;
		}
   }

void Obstacle::ajoute_a(Systeme& S){
	S.ajoute(this);
	cout << "une brique est ajouté au systeme"<<endl;
	 }



//__________________________________________________________________________________________________________________________
// Plan
	
	
 Vecteur Plan::n() const { 	// On définit la normale au plan, qui correspond au produit vectoriel des vecteurs directeurs du plan
     return (!(dir1^dir2));
 }


//on redefinit la methode de point le plus proche
Vecteur Plan::point_plus_proche(const ObjetMobile& M){
		Vecteur x2;
		Vecteur n (this->n()); 	//normale au plan
		Vecteur position (M.position());	//position de l'objet
        	double point (( obs_origine - position ) | n);
       		x2 = position + point*n;	//formule du point le plus proche
		return x2;
}
    
    
Plan* Plan::copie() const {	 //pour pouvoir utiliser la methode copieobjet
        return (new Plan(*this));}

	 
//Operateur d affichage
void Plan::affiche() const{
	cout << "Un plan est constitué de: " << endl;
		
		cout << obs_origine << "  #origine" << endl;
		for (size_t i(0); i< n().taille();i++){
			cout << n().getcomposante(i) << " ";}
		cout << "  #normale" << endl;
		cout << endl;
}
ostream& operator<<(ostream& sortie, Plan const& P){
	P.affiche();
	return sortie;
}

void Plan::dessine_sur(SupportADessin& support) { support.dessine(*this); }

    
//______________________________________________________________________________________________________________________________________________
//Brique    

Vecteur point_portion (ObjetMobile const& M, Vecteur dir1, Vecteur dir2, Vecteur point){
	Plan face (point, dir1, dir2);	//On forme un plan avec les vecteurs directeurs de la face de la brique, pour pouvoir utiliser la methode propre au plan du point le plus proche
	return face.point_plus_proche(M);
}

    /// a retirer si ca marche avec la methode de plan
    Vecteur Brique::n() const {
     return (!(largeur^longueur));	//Axe ZxX
 }


    Vecteur Brique::point_plus_proche(const ObjetMobile& M){
        // But: faire le point le plus proche de chaque face puis garder la plus petite distance
	 bool debut (true);		// Ce booleen pourra permettre de determiner si une valeur de distance par rapport à une face de la brique a déjà été calculée ou non (voir plus loin pour son utilisation)
         Vecteur point_proche (vecnull);
         double meilleure_distance;
         Vecteur n (this-> n());	//norme à la portion de plan
         Vecteur h (-hauteur*n);	// vecteur pour la hauteur (car l'attribut hauteur est un double)
         Vecteur a(!longueur); 		//a donne la direction de la longueur
         Vecteur b(!largeur);		//b donne la direction de la largeur
         array<array<Vecteur,6>,6> tableau ({obs_origine,n,longueur,a,largeur,b,	//Ce tableau est visible dans le complement mathematique du projet
                                obs_origine,-b,h,-n,longueur,a,
                                obs_origine,-a,largeur,b,h,-n,
                                obs_origine+longueur,a,h,-n,largeur,b,
                                obs_origine+largeur,b,longueur,a,h,-n,
                                obs_origine+h,-n,largeur,b,longueur,a});
                    
        Vecteur point2;        
        //l'idee est de faire une boucle pour trouver quelle est la face la plus proche
        for (int i(0);i<6; i++){
            
            //calcule pour un plan infini: on appelle une fonction qui assimile cette portion de plan comme un plan ce qui permet d'utiliser la fonction point_plus_proche de plan
            point2 = ( point_portion (M, tableau[i][3], tableau[i][5], tableau[i][0]));
                      
            //calcul des coordonnées: voir le complément mathématique pour les opérations
             
            double xLg( (point2-tableau[i][0]) | tableau[i][3] );	 //Pour faire le projeté sur la longueur
            double xlar ( (point2-tableau[i][0]) | tableau[i][5] );	 //Pour faire le projeté sur la largeur
            if (xLg - (tableau[i][2]).norme() > epsilon){ 		 //si xLg >L alors on modifie pour retrouver le point le plus proche
                point2-= (xLg- (tableau[i][2]).norme()) * tableau[i][3];
            }
            else if (xLg < epsilon){
		point2-= xLg*tableau[i][3];
	    }

            if ( ( xlar - tableau[i][4].norme() ) > epsilon){
		point2-= (xlar-tableau[i][4].norme()) * tableau[i][5];
	    }
            else if (xlar<epsilon) {
		point2-= xlar*tableau[i][5];
	    }
            
            
            // Pour savoir quelle est la meilleure distance :
            Vecteur A (M.position()-point2);
            if (debut) {
		point_proche=point2;
                meilleure_distance= A.norme()-M.getrayon();
                debut = false;
            }
            else if (meilleure_distance - (A.norme()-M.getrayon()) > epsilon) {
		point_proche=point2;
                meilleure_distance= (A.norme()-M.getrayon());
	    }
            
            
        }
    return point_proche;
}

Vecteur Brique::getlongueur() const { return longueur;}
Vecteur Brique::getlargeur() const {return largeur;}
double Brique::gethauteur() const {return hauteur;}


Brique* Brique::copie() const { 
        return (new Brique(*this));}



//Operateur
void Brique::affiche() const{
	cout <<"Une brique constituée de: " << endl;
		for (size_t i(0); i< getobs_origine().taille();i++){
			cout << obs_origine.getcomposante(i) << "  ";}
	cout << "  #origine"<< endl;
		
		for (size_t i(0); i< getlongueur().taille();i++){
			cout << longueur.getcomposante(i) << "  ";}
		cout << "  #longueur"      << endl;
		
		for (size_t i(0); i < getlargeur().taille();i++){
		cout << getlargeur().getcomposante(i) << "  ";}
		cout << "  #largeur" << endl;

		cout << gethauteur() << "  #hauteur" << endl;
		cout << endl;
}


ostream& operator<<(ostream& sortie, Brique const& B){
	B.affiche();
	return sortie;
}


void Brique::dessine_sur(SupportADessin& support) { support.dessine(*this); }
