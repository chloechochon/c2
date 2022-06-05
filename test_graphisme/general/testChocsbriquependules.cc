#include <iostream>
#include "ObjetMobile.h"
#include "Integrateur.h"
#include "constantes.h"
#include "obstacle.h"
#include <cmath>

using namespace std;

//Ce fichier test permet de tester l'efficacité des fonctions de chocs avec un intégrateur: 

int main () {
IntegrateurEulerCromer I (0.01);
IntegrateurNewmark K (0.01);
unsigned int n (50);
//On teste un Pendule et une brique

//creation brique
Vecteur ori_brique(2.0,2.0,0.0);
Vecteur longueur(0.0,1.0,0.0);
Vecteur largeur(1.0,0.0,0.0);
double hauteur(2);
Brique brique (ori_brique, longueur, largeur, hauteur);

//On crée un nouveau pendule qu'on place à côté de la brique
Vecteur theta4(M_PI_4);
Vecteur thetapoint4(0);
double m4(1);
double rayon4(0.1);
Vecteur ori4(0.0,4.0,0.0);
double l4(4);
Vecteur dir(1.0,0.0,0.0);
Pendule p4 (theta4, thetapoint4, m4, vecnull, rayon4, ori4, l4, dir);


for (size_t i(1); i < n; ++i) {
    cout << "l'intégration " << i << " donne :" << endl;
    I.integre (p4);
    if ( brique.distance(p4) < epsilon){
		brique.agit_sur(p4);
	}
	cout << "Pendule : " << endl;
    p4.affiche();
    cout << endl;
}
return 0;
}
