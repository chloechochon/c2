#include "Integrateur.h"
#include "ObjetMobile.h"
#include "ex_vecteur.h"
#include <vector>
#include <iostream>

using namespace std;


int main (){
	
    Vecteur pos (0, 5 ,0);
    Vecteur vit (0, 0, 0);
    double masse (1);
    Vecteur f (0, -0.591725259488945, 0);
    Balle b ( pos, vit, masse, f , 0.1) ;

	b.affiche();
	cout << endl;

    unsigned int n(500);	//le nombre d'intervalles sur lesquels on intègre

	IntegrateurEulerCromer I (0.01); //intégrateur avec un pas de temps de 0.01 seconde
    
    
    for (size_t i(1); i < n; ++i) {
    cout << "l'intégration " << i << " donne :" << endl;
    I.integre (b);
    b.affiche();
    cout << endl;
    }
    
    
    //On observe désormais un pendule avec le même intégrateur EulerCromer
    Vecteur theta (0.4);
    Vecteur thetapoint (2);
    double m (1);
    double r (0.1);
    Vecteur ori (0, 5, 0);
    double l (1);
    Vecteur d (1, 0, 1);
    
    Pendule p (theta, thetapoint, m, vecnull, r, ori, l, d);
    
    p.affiche();
    cout << endl;

    for (size_t i(1); i < n; ++i) {
    cout << "l'intégration " << i << " donne :" << endl;
    I.integre (p);
    p.affiche();
    cout << endl;
    }
   /* 
./testIntegrateur2 | grep '#position' > posballe.txt
./testIntegrateur2 | grep '#theta du pendule' > anglependule.txt
*/
return 0;
}


