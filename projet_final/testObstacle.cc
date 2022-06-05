#include <iostream>
#include <vector>
#include <array>
#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "constantes.h"
#include "obstacle.h"
using namespace std;

int main (){
	
	//pour initialiser la balle
	Vecteur vit(0.0 , 0.0 , 0.0);
	Vecteur pos(1.5,-0.5,0.5);		// face de droite
	Vecteur F(0,-0.591725259488945,0);
	Balle b(pos,vit,0.100530964914873,F,0.2);
	b.affiche();
	
	//pour initialiser le plan
	Vecteur orig(0.0,0.0,0.0);
	Vecteur di1(0.0,0.0,1.0); 
	Vecteur di2(1.0,0.0,0.0); 
	Plan P(orig,di1,di2);
	P.affiche();
	
	//pour initialiser la brique 
	Vecteur ori(0.0,0.0,0.0);
	Vecteur lalongueur(1.0,0.0,0.0); 
	Vecteur lalargeur(0.0,0.0,1.0); 
	double hauteur(1.0);
	Brique B(ori,lalongueur,lalargeur,hauteur);
	B.affiche();
	
	//pour point le plus proche
	
	//Face 1 a droite
	cout<<"test :"<<endl;
	cout<<endl;
	cout << "Face 1 a droite: " << endl;
	cout<< P.point_plus_proche(b) ;
	cout<<"  #point le plus proche du plan"<<endl;
	cout<<endl;
	
	cout<<P.distance(b);
	cout<<"  #distance au plan"<<endl;
	cout<<endl;

	cout << "Position balle: "<< b.position()<< endl;
	cout<<B.point_plus_proche(b);
	cout<<"  #point le plus proche de la brique" <<endl;
	cout<<endl;

	cout<<B.distance(b);
	cout<<"  #distance à la brique"<<endl;
	cout<<endl;
	cout << endl;

	//-----------------------------------------------
	//Face 2 devant
	b.setposition({0.5,-0.5,1.5});
	cout << "Face 2 devant: " << endl;
	cout<<"Je deplace la balle en " << b.position() <<endl;
		
	cout<< P.point_plus_proche(b);
	cout<<"  #point le plus proche du plan"<<endl;
	cout<<endl;

	cout << P.distance(b);
	cout<<"  #distance au plan"<<endl;
	cout<<endl;

	cout << B.point_plus_proche(b);
	cout<<"  #point le plus proche de la brique "<<endl;
	cout<<endl;

	cout<< B.distance(b);
	cout<<"  #distance à la brique"<<endl;
	cout<<endl;
	cout << endl;
	
		//-----------------------------------------------
	//Face 3 à gauche
	b.setposition({-0.5,-0.5,0.5});
	cout << "Face 3 à gauche: " << endl;
	cout<<"je deplace la balle en " << b.position() <<endl;	

	cout<<P.point_plus_proche(b);
	cout<<"  #point le plus proche du plan"<<endl;
	cout<<endl;

	cout<<P.distance(b);
	cout<<"  #distance au plan"<<endl;
	cout<<endl;

	cout<<B.point_plus_proche(b);
	cout<<"  #point le plus proche de la brique"<<endl;
	cout<<endl;

	cout<<B.distance(b);
	cout<<"  #distance à la brique"<<endl;
	cout<<endl;
	cout << endl;

			//-----------------------------------------------
	//Face 4 derriere
	b.setposition({0.5,-0.5,-0.5});
	cout << "Face 4 derrière: " << endl;
	cout<<"je deplace la balle en " << b.position()<<endl;
	cout<<endl;

	cout << P.point_plus_proche(b);
	cout<<"#point le plus proche du plan"<<endl;
	cout<<endl;

	P.distance(b);
	cout<<"#distance au plan"<<endl;
	cout<<endl;

	cout << B.point_plus_proche(b);
	cout<<" #point le plus proche de la brique"<<endl;
	cout<<endl;
	
	cout << B.distance(b);
	cout<<" #distance à la brique"<<endl;
	cout<<endl;
	cout << endl;

//-----------------------------------------------
	//Face 5 au dessus
	b.setposition({0.5,0.5,0.5});
	cout << "Face 5 au dessus: "<< endl;
	cout<<"je deplace la balle en " << b.position() <<endl;
	cout<<endl;
	
	cout<<"test"<<endl;
	cout<<P.point_plus_proche(b);
	cout<<"  #point le plus proche du plan"<<endl;
	cout<<endl;

	cout<<P.distance(b);
	cout<<"  #distance au plan"<<endl;
	cout<<endl;

	cout << B.point_plus_proche(b);
	cout<<"  #point le plus proche de la brique"<<endl;
	cout<<endl;
	
	cout << B.distance(b);
	cout<<"  #distance"<<endl;
	cout<<endl;
	cout << endl;
//-----------------------------------------------------
//Face 6 en dessous
	b.setposition({0.5,-1.5,0.5});
	cout << " Face 6 en dessous: " << endl;
	cout<<"je deplace la balle en " << b.position() <<endl;
	cout<<endl;
	
	cout<<P.point_plus_proche(b);
	cout<<"  #point le plus proche du plan"<<endl;
	cout<<endl;

	cout<<P.distance(b);
	cout<<"  #distance au plan"<<endl;
	cout<<endl;

	cout << B.point_plus_proche(b);
	cout<<"  #point le plus proche de la brique"<<endl;
	cout<<endl;
	
	cout << B.distance(b);
	cout<<"  #distance à la brique"<<endl;
	cout<<endl;
	cout << endl;
	cout << endl;
	cout << "FINIIIIIIIIIIIIIIIIIIIII" << endl;
	return 0;}
