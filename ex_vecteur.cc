

#include <iostream>   
#include <vector>
#include "ex_vecteur.h"
#include <cmath>
using namespace std;


    double Vecteur::getcomposante(size_t i) const {return vecteur[i];}

    size_t Vecteur::taille() const {return vecteur.size();}
    
   void Vecteur::dimension(Vecteur autre){	//pour gerer le cas où les vecteurs sont de taille differente
	if (taille()!=autre.taille()){
	   size_t nv (taille());
      	   size_t na (autre.taille());
	   cout << "Attention les vecteurs sont de tailles différentes!" << endl;
           if (nv > na){
                for (size_t i(na); i < nv; ++i){
                    autre.augmente(0.0);
                }
            }else{
                for (size_t i(nv); i < na; ++i){
                    augmente(0.0);
                }
            }
	}
}
		

    
   vector<double> Vecteur::getvecteur() const {return vecteur;}
   
   void Vecteur::setvecteur(vector<double> vec){vecteur=vec;}



    void Vecteur::augmente(double aug){         //ajoute une dimention au vecteur en y ajoutant la valeur passee en argument
        vecteur.push_back(aug);
    }
   
//__________________________________________________________________________________________________
    
    void Vecteur::set_coord(size_t coord, double valeur){
        vecteur[coord]=valeur;
    }

//_____________________________________________________________________________________________________

  

 ostream& operator<<(ostream& sortie, Vecteur const& v){
for (size_t i(0); i<v.taille();i++) {
sortie << v.getcomposante(i) << " ";
}
return sortie;

}

//__________________________________________________________________________________________________

    

bool Vecteur::operator==(const Vecteur& v) const {
    if (vecteur.size() != v.getvecteur().size()){
        //les vecteurs sont differents
        return false;
    }else{
    int a(0);
    for(size_t i(0);i<v.taille();i++){
        if (vecteur[i]-v.vecteur[i] > 0.0000001){ //on ne peut pas comparer deux doubles ensembles
            a=1;
        }
    }
    if (a==0) {return true;}
    else {return false;}
    }
}
 
//_____________________________________________________________________________________________

 
   Vecteur Vecteur::operator+=(const Vecteur& autre){
        double valeur;
        if (taille()!=autre.taille()){
		dimension(autre); // pour tester si les dimensions sont les meme et les modifier sinon 
	}
        for (size_t i(0); i < taille() ; ++ i ){
               valeur=(*this).getcomposante(i)+autre.getcomposante(i);
               set_coord(i,valeur);
               }
             return (*this);
        }
    
    Vecteur Vecteur::operator+(const Vecteur& autre) const{
		Vecteur nv (*this);
        return nv+= autre;
    }

//________________________________________________________________________________________

    
    
    Vecteur Vecteur::operator-() const{
		Vecteur nv;
        for (size_t i(0); i < taille() ; ++ i ){
                nv.augmente (-vecteur[i]);
        }
        return nv;
        }
//_______________________________________________________________________________________________________________________

    

 
    
    Vecteur Vecteur::operator-=(const Vecteur& autre){
        double valeur;   
		dimension(autre); // pour tester si les dimensions sont les meme et les modifier sinon 
		for (size_t i(0); i < taille() ; ++ i ){
			valeur=(*this).getcomposante(i)-autre.getcomposante(i);
			set_coord(i,valeur);
			}
		
        return (*this);
        }
             
    Vecteur Vecteur::operator-(const Vecteur& autre) const {
		Vecteur nv (*this);
        return nv-= autre;
    }
    
//______________________________________________________________________________________________________________-

   
    Vecteur Vecteur::operator*=(const Vecteur& autre){
        double valeur;    
        if ((taille()== autre.taille()) and  (taille()==1)){       //la multiplication entre deux vecteurs ne peux se faire  que si c'est de une dimention, sinon on utilise le produit scalaire ou vectorielle     
               valeur=(*this).getcomposante(0)*autre.getcomposante(0);
               set_coord(0,valeur);
        
	} else {
		cout << "la multiplication ne s'est pas faite , il faudrait mieux utiliser le produit scalaire ou vectoriel car les vecteurs sont de taille superieure a 1" << endl;
	}
     return (*this);
    }
             
    Vecteur Vecteur::operator*(const Vecteur& autre) const {
		Vecteur nv (*this);
        return (nv*= autre);
    }
    
     Vecteur operator*(double lambda, Vecteur const& V) {
         double valeur;    
         Vecteur nv;                
         for (size_t i(0); i < V.taille() ; ++ i ){
             valeur=V.getcomposante(i)*lambda;
             nv.augmente(valeur);
         }
        return nv;
    }

Vecteur Vecteur::operator*(const double lambda) const {
	return (lambda*(*this));
}

//___________________________________________________________________________________________---

   
    double Vecteur::operator|(const Vecteur&  autre) const { //produit scalaire
        double a (0);
        if (taille() == autre.taille()){
       		for (size_t i(0); i < vecteur.size(); ++i){
            		a += vecteur[i]*autre.vecteur[i];
            	}
        }else {
            cout <<"Les dimensions ne sont pas semblables, erreur pour le produit scalaire"<<endl;
        }
    return a;
   }


//____________________________________________________________________________________________

  
    Vecteur Vecteur::operator^(const Vecteur&  autre) const {	//produit vectoriel, uniquement pour les vecteurs de dimension 3
        Vecteur prod({0.0,0.0,0.0});
        if ((taille()!=3) or (autre.taille()!=3)){
            cout << "Les dimensions ne sont pas appropriées, erreur pour le produit vectoriel"<<endl;
        } else {
            prod.vecteur = {vecteur[1]*autre.vecteur[2] - vecteur[2]*autre.vecteur[1],
                            vecteur[2]*autre.vecteur[0] - vecteur[0]*autre.vecteur[2],
                            vecteur[0]*autre.vecteur[1] - vecteur[1]*autre.vecteur[0]
                            };
        }
        return prod;
        }
//____________________________________________________________________________________________________________

    double carre(double a){
        return a*a;
    }

//_________________________________________________________________________________________________

    double Vecteur::norme2() const {
        double norme2 (0);
        for (size_t i(0); i < vecteur.size(); ++i){
            norme2 += carre(vecteur[i]);
        }
        return norme2;
    }

//___________________________________________________________________________________________________

    double Vecteur::norme() const {
        double norme (sqrt(norme2()));        
        return norme;
    }

//_____________________________________________________________________________________________________________

    
   Vecteur Vecteur:: operator!() const{
       double n (norme());
       Vecteur nv(*this);
       if (n > 0.000001){
			Vecteur unitaire ((1/n)*nv);
			if(unitaire.norme()-1<0.00000001){
			}else{ cout << "vecetur unitaire incorrect"<<endl;}
			return unitaire;
	}else{
		cout << "Ce vecteur n'existe pas, n'a pas de norme." << endl;
		Vecteur vecnull (0,0,0);
		return vecnull;
       }
   }

//________________________________________________________________________________________________________________






