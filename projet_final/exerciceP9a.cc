#include "Integrateur.h"
#include "ObjetMobile.h"
#include "ex_vecteur.h"
#include "Systeme.h"
#include "obstacle.h"
#include <vector>
#include <iostream>
#include <memory>
using namespace std;


int main (){
	///est ce que j'utilise bien le constructeur la ?? (je veux farie comme si j'avais initialiser dans le constructeur des tableaux nuls
    Systeme le_systeme;
	
    //On a construit la balle (en 2D selon les instructions de l'exercice de P7)
    Vecteur pos (0, 0,0);
    Vecteur vit (1.5, 2.0,0.0);
    double masse (0.127);
    Balle b (pos,vit,masse,vecnull);

    // on va utiliser la copie polymorphique avec des unique ptr
    le_systeme.ajoute(new Balle (b));
 
    //construction d'un obstacle (ici un plan)
	Vecteur orig({0.0,0.0,0.0});
	Vecteur di1({0.0,1.0,0.0}); 
	Vecteur di2({1.0,0.0,0.0}); 
    Plan P(orig,di1,di2);
	
    //meme idee qu'avant mais ici on ajoute un systeme
    le_systeme.ajoute(new Plan (P));


    // On souhaite faire une etude du mouvement de la balle avec l integrateur sur n intervalles de dt seconde car on utilise les meme condition que l'exercice P7
    unsigned int n;
    do{
        cout << "Sur combien d'intervalles de temps voulez-vous étudier le mouvement de la balle? ";
        cin >> n;
    } while ( n <=0);
    
    double dt;
    cout << "quel est le dt ?" <<endl;
    cin >> dt;
    cout << endl;
    
    int mon_integrateur;
    do {
		cout << " quel integrateur voulez vous utilisé (rentrer 1 pour integrateurNewmark, 2 pour IntegrateurEulerCromer)" << endl;
		cin >> mon_integrateur;
		} while ((mon_integrateur==1) or (mon_integrateur==2));
    
	cout<< "avant l'evolution : " << endl;
	le_systeme.affiche();
	cout<< endl;
	
	cout << endl;
		
		for (size_t i(0); i <n; i++){
		cout <<" evolution ... "<<endl;
		cout << endl;
		le_systeme.evolue2(dt, mon_integrateur);
		
}


   	
    cout<< endl;
    
    


return 0;
}



