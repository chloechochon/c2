#include "Dessinable.h"
#include "Systeme.h"
#include "ex_vecteur.h"
#include "Integrateur.h"
#include "ChampsForces.h"
#include "ObjetMobile.h"
#include "obstacle.h"
#include "Objetcompose.h"
#include <memory>
#include <map>



using namespace std;

void Systeme::dessine_sur(SupportADessin& support) { support.dessine(*this); }

void Systeme::affiche() const {
    cout << "Le système est composé de : " <<endl;
    cout << endl;
    unsigned int n(tableau_objets.size());

    if (n != 0){
        if (n == 1){
            cout << "Un objet mobile: " << endl;
        }else{
            cout<< n << " objets mobiles: "<< endl;
        }
        for (size_t i(0); i < n; ++i){
        (*tableau_objets[i]).affiche();		/// Verifier comment prendre la valeur du pointeur et les include suite a l utilisation d unique ptr
        cout<<endl;
        }
    }else{
        cout << "Aucun objet mobile." << endl;
    }
    
    cout << endl;
    
    n = tableau_obstacles.size();
    if (n != 0){
        if (n == 1){
             cout << "Un obstacle: "<< endl;
        }else{
            cout << n << " obstacles: " << endl;
        }
        for (size_t i(0); i < n; ++i){
         (*tableau_obstacles[i]).affiche();		/// Verifier comment prendre la valeur du pointeur et les include suite a l utilisation d unique ptr
        cout<<endl;
        }
    }else{
        cout << "Aucun obstacle." << endl;
    }       
            
    
  n = tableau_champs.size();
    if (n != 0){
        if (n == 1){
             cout << "Un champ de force: "<< endl;
        }else{
            cout << n << " champs de force: " << endl;
        }
        for (size_t i(0); i < n; ++i){
         (*tableau_obstacles[i]).affiche();		/// Verifier comment prendre la valeur du pointeur et les include suite a l utilisation d unique ptr
        cout<<endl;
        }
    }else{
        cout << "Seule la gravité et la force d'Archimede agissent" << endl;
    }
    cout << endl;
}


ostream& operator<<(ostream& sortie,const Systeme& Sys){
    Sys.affiche();
    return sortie;
}


void Systeme::evolue2(double dt, int integrateur) {
cout <<"a evolue" << endl; 

    //ajoutons les forces externes que subissent les objet mobiles (les champs de forces)
    for(size_t i(0); i<tableau_champs.size(); i++){
		for(size_t j(0); j<tableau_objets.size(); j++){
			(*tableau_champs[i]).agit_sur(*tableau_objets[j]);
		}
	}

    //pour calculer le cas ou il pourrait y avoir un choc
    for(size_t i(0); i<tableau_objets.size(); i++){
        for(size_t j(i+1); j<tableau_objets.size(); j++){ //pour que les objet ne ce touche u'une fois le debut de la deuxieme boucle est i
            (*tableau_objets[i]).agit_sur((*tableau_objets[j]));
        }
    }

    //et enfin integre l'objet qui "deplace" les objets
		for(size_t k(0); k<tableau_objets.size(); k++){ 
	   if (integrateur==1) {

		IntegrateurNewmark inte(dt);
        inte.integre(*tableau_objets[k]); 
        (*tableau_objets[k]).affiche();
        
		} else {
			
        IntegrateurEulerCromer inte(dt);
        inte.integre(*tableau_objets[k]); 
        (*tableau_objets[k]).affiche();
	}

    

    }
}

void Systeme::ajoute(ObjetMobile* objet){
    tableau_objets.push_back(unique_ptr <ObjetMobile> (objet->copie()));
}
void Systeme::ajoute(Obstacle* obstacle){
    tableau_obstacles.push_back(unique_ptr <Obstacle> (obstacle->copie()));
}

void Systeme::ajoute(ChampForces* Champ){
	int num (Champ->getnumero());
   for (size_t i(0); i < taille_tab_obj(); ++i){
    retour_obj(i)->setdanschamp(num, false);
	}
	tableau_champs.push_back(unique_ptr <ChampForces> (Champ->copie()));

}


size_t Systeme::taille_tab_obj () const {
    return tableau_objets.size();
}
size_t Systeme::taille_tab_obs () const {
    return tableau_obstacles.size();
}
size_t Systeme::taille_tab_champs () const {
    return tableau_champs.size();
}
unique_ptr<ObjetMobile> Systeme::retour_obj (size_t i) const {
    return unique_ptr <ObjetMobile> (tableau_objets[i]->copie());
}
unique_ptr<Obstacle> Systeme::retour_obs (size_t i) const {
    return unique_ptr <Obstacle> (tableau_obstacles[i]->copie());
}
unique_ptr<ChampForces> Systeme::retour_champ (size_t i) const {
    return unique_ptr <ChampForces> (tableau_champs[i]->copie());
}

