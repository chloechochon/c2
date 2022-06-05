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

//chocs Balle/plan

//pour initialiser la balle
double masse3(0.00167784948285945);
	Vecteur pos3(0, 0.3, 0);
    Vecteur vit3(0,2.0,0.8);
    Balle b3(pos3, vit3,masse3, vecnull,0.051111,  3,0.8,0.01);  ///attention je suis pas sur qu'il faille ajouté g ici peut etre qu'on l'a mis deux fois !! =>non ca aurait ete si on utilisait la fonction evolue2

   cout << " force : " << b3.getforce()<<endl;
cout << endl;
b3.affiche();
cout <<endl;
cout <<"blabla" <<endl;
//pour initialiser le plan
	Vecteur orig(0.0,0.0,0.0);
	Vecteur di1(0.0,0.0,1.0); 
	Vecteur di2(1.0,0.0,0.0); 
	Plan P(orig,di1,di2);
	P.affiche();

cout << "champs de force" <<endl;
cout << b3.getforce()<< endl;

for (size_t i(1); i < n; ++i) {
    cout << "l'intégration " << i << " donne :" << endl;
    I.integre (b3);
    cout << " distance au plan : " << P.distance(b3)<<endl;

	P.agit_sur(b3);
	cout << "Balle : " << endl;
    cout << b3.position() << "#position" <<  endl;
        cout <<  b3.vitesse() << "vitesse : " <<endl;


    cout << endl;
}
 return 0;
}
