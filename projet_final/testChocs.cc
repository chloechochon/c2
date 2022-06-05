#include <iostream>
#include <vector>
#include "ObjetMobile.h"
#include "obstacle.h"
#include "constantes.h"

using namespace std;

int main() {
	//Attention lire ces lignes !
	//on est ici dans le cas on on gere juste le choc entre deux objets et pas un systeme l'evolution d'un systeme entier
	
	//pour les chocs entre un objet mobile est un obstacle
	
	
		//sachant qu'on a pris comme repere l'axe z qui sort du plan et l'axe y vers le haut il y a des changements

	//construction de la balle 1
	double masse(0.00167784948285945);
	Vecteur pos(0, 0.0465234, 0.624);
    Vecteur vit(0, -2.59108, 0.8);
    Balle b1(pos, vit,masse, vecnull,0.051111, 3,0.8,0.01);  ///attention je suis pas sur qu'il faille ajouté g ici peut etre qu'on l'a mis deux fois !! =>non ca aurait ete si on utilisait la fonction evolue2
    cout <<"test" << endl;
	//changement d'axe: c'est donc l'axe y qui vaut 0
	//construction du plan 
	Vecteur ori(0.0,0.0,0.0);
	Vecteur di1(1.0,0.0,0.0); 
	Vecteur di2(0.0,0.0,1.0); 
    Plan P(ori,di1,di2);
	
	
	//affichage
	cout<<"cas 1"<<endl;
	cout<<endl;
	cout<<"vitesse="<<b1.getPd()<<endl;
	cout<<"force ="<<b1.getforce()<<endl;
	cout <<endl;
		
	//choc
	P.agit_sur(b1);  ///je coris qu'on est bien avant le pas d'integration 
	///est ce que j'integre ? (le pesne pas si on se dit que le choc se faitdans in temps negligeable (les balles (ou obstacles et balles) se touchent deja donc pas besoin de les deplacer)
	
	cout<<endl;
	cout <<endl;
	
	//------------------------------------------------------------------------------------------
	//pour les chocs entre 2 balles (les balles sont appelés balle 2 et balle 3)
	
	//construction de la balle 2
	Vecteur pos2(0,0.283821,1.36675);
    Vecteur vit2(0,0.0957368,0.715449);
    Balle b2(pos2, vit2, masse ,vecnull, 0.051111,  3.0, 0.8,0.01);

	//construction de la balle 3
	Vecteur pos3(0, 0.260128, 1.46284);
    Vecteur vit3(0, 0.13874, 0.419218);
    Balle b3(pos3, vit3, 0.1 , vecnull,0.05, 3.0, 0.8);

	cout<<"cas 2"<<endl;
	cout<<endl;
	cout<<"avant le choc" <<endl;
	cout << "position de la balle 1 = " << b2.position()<<endl;
	cout << "position de la balle 2 = " << b3.position()<<endl;
	cout << " Distance entre les centres: " << (pos2-pos3).norme() << endl;
	cout<<"vitesse de la balle 1 ="<<b2.getPd()<<endl;
	cout<<"vitesse de la balle 2 ="<<b3.getPd()<<endl;

	cout<<"force de la balle 1 ="<<b2.getforce()<<endl;
	cout<<"force de la balle 2 ="<<b3.getforce()<<endl;
	cout <<endl;
	
	//choc
	
	b2.agit_sur(b3); 
	 
	cout<<endl;

	//apres choc
	cout<<"apres le choc: "<<endl;
	
	cout<<"vitesse de la balle 1 ="<<b2.getPd()<<endl;
	cout<<"vitesse de la balle 2 ="<<b3.getPd()<<endl;

	cout<<"force de la balle 1 ="<<b2.getforce()<<endl;
	cout<<"force de la balle 2 ="<<b3.getforce()<<endl;

///faudrait faire le test avec un pendule aussi
	Vecteur origine (0, 1.209488037945800, 1.148649741794006);
	Vecteur d (1,0,0);
	Vecteur f ( 0, -0.096839923502870, -0.292612361619043 );
    Pendule p(0.319603599172218, 0.441579572811062, 0.1 , f, 0.05, origine, 1.0, d);
    b2.setposition (pos3);
    b2.setvitesse (vit3);

    
   
   cout<< "test avec le pendule: " << endl;
	cout<<endl;
	cout<<"avant le choc" <<endl;
	cout << "position de la balle = " << b2.position()<<endl;
	cout << "position au bout du pendule " << p.position()<<endl;
	cout << " Distance entre les centres: " << (p.position() - b2.position()).norme() << endl;
	cout<<"vitesse de la balle = "<<b2.getPd()<<endl;
	cout<<"vitesse du pendule = "<<p.getPd()<<endl;

	cout<<"force de la balle = "<<b2.getforce()<<endl;
	cout<<"force du pendule = "<<p.getforce()<<endl;
	cout <<endl;
	
	p.agit_sur(b2);
	
	//apres choc
	cout<<"apres choc: "<<endl;
	
	cout<<"vitesse de la balle2 ="<<b2.getPd()<<endl;
	cout<<"vitesse du pendule ="<<p.vitesse()<<endl;

	cout<<"force de la balle ="<<b2.getforce()<<endl;
	cout<<"force du pendule ="<<p.getforce()<<endl;
	}

/*
 * Les ChampForces et les Obstacles doivent être deux classes séparées en raison de la gestion (ultérieure) de la simulation
 * (en bref, agit_sur() des ChampForces ajoute une force alors que celui des Obstacles modifie la vitesse (choc)).
 * Ces obstacles sont donc des objets qui vont aussi «agir_sur()» les ObjetMobiles et dont nous aurons uniquement besoin de connaître la position, ainsi que de pouvoir calculer le point le plus proche à un objet mobile (cf compléments mathématiques).
 * Il nous faudra d'ailleurs généraliser ceci également aux ObjetMobiles eux-mêmes pour gérer les chocs entre eux
 * (nous nous occuperons de la gestion des chocs eux-même dans deux semaines).
*/
