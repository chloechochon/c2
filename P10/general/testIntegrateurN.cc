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

    Vecteur theta (0.4);
    Vecteur thetapoint (2);
    double m (1);
    double r (0.1);
    Vecteur ori (0, 5, 0);
    double l (1);
    Vecteur d (1, 0, 1);
    Pendule p (theta, thetapoint, m, vecnull, r, ori, l, d);
    
    
    unsigned int n(100);	//le nombre d'intervalles sur lesquels on intègre
    IntegrateurNewmark K (0.01);
    
    
    //Integration de la balle
	b.affiche();
	cout << endl;

    for (size_t i(1); i < n; ++i) {
    cout << "l'intégration " << i << " donne :" << endl;
    K.integre (b);
    b.affiche();
    cout << endl;
    }
    
    /*
    //Integration du pendule
    p.affiche();
    cout << endl;

    for (size_t i(1); i < n; ++i) {
    cout << "l'intégration " << i << " donne :" << endl;
    K.integre (p);
    p.affiche();
    cout << endl;
    }
*/

return 0;
}


