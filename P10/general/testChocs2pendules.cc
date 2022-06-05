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


//On teste deux pendules ensemble:
Vecteur theta2(M_PI_4);
Vecteur thetapoint2(0);
double m2(1);
double rayon2(0.1);
Vecteur ori2(0,4.1,0);
double l2(4);
Vecteur dir2(1.0,0.0,0.0);
Pendule p2 (theta2, thetapoint2, m2, vecnull, rayon2, ori2, l2, dir2);

Vecteur theta3(M_PI_4);
Vecteur thetapoint3(0);
double m3(1);
double rayon3(0.1);
Vecteur ori3(2.0,4.1,0.0);
double l3(4);
Vecteur dir3(-1.0,0.0,0.0);

Pendule p3 (theta3, thetapoint3, m3, vecnull, rayon3, ori3, l3, dir3);

for (size_t i(1); i < n; ++i) {
    cout << "l'intégration " << i << " donne :" << endl;
    I.integre (p2);
    K.integre (p3);
	p2.agit_sur(p3);
	
	cout << "Pendule 1 : " << endl;
    p2.affiche();
    cout << endl;
    cout << "Pendule 2 : " << endl;
    p3.affiche();
    cout << endl;
}
return 0;
}
