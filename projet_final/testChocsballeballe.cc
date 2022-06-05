#include <iostream>
#include "ObjetMobile.h"
#include "Integrateur.h"
#include "constantes.h"
#include "obstacle.h"
#include <cmath>

using namespace std;


int main () {
IntegrateurEulerCromer I (0.01);
IntegrateurNewmark K (0.01);
unsigned int n (50);



// On commence par tester les chocs Balle/Balle
Vecteur pos1 (0,0,0);
Vecteur vit1 (7*sqrt(2), 7*sqrt(2), 0);
Vecteur pos2 (2,2,0);
Vecteur vit2 (0, 0, 0);
double masse1(1);
double masse2(2);

Balle b1 (pos1, vit1, masse1, vecnull);
Balle b2 (pos2, vit2, masse2, vecnull);

cout << "balle 1: " << endl;
b1.affiche();
cout << endl; 
cout << "balle 2 : " << endl;
b2.affiche();
cout << endl; 


//On utilise un intégrateur différent pour chaque balle: EulerCromer pour b1 et Newmark pour b2



    for (size_t i(1); i < n; ++i) {
    cout << "l'intégration " << i << " donne :" << endl;
    I.integre (b1);
    I.integre (b2);
   if (((b1.position()-b2.position()).norme() - (b1.getrayon() + b2.getrayon())) < epsilon){
		b1.agit_sur(b2);
	}
    b1.affiche();
    cout << endl;
    b2.affiche();
    cout << endl;
    }
   return 0;
  }
 


