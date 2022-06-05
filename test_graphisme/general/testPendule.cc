#include "ex_vecteur.h"
#include "ObjetMobile.h"
#include "constantes.h"
#include "Integrateur.h"
#include <iostream>
#include <cmath>
using namespace std;

    
int main (){
    //creation d'un pendule
    Vecteur theta (0.4);
    Vecteur vit_ang (0);
    double m (0.1);
    Vecteur F (m*g);
    cout << "F: " << F << endl;
	Vecteur d (1.0, 0.0, 0.0);
    double r (0.2);
    Vecteur Or (0.0, 1.0, 2.0);
    double longueur (2);
    double frottement (2.0*m);
    Pendule p (theta, vit_ang, m, F, r, Or, longueur, d, 1, 0, 1, frottement);
    cout <<"Nous avons : " <<endl;
    p.affiche();
    cout << p.evolution() << "  #accélération" << endl;
    cout<<endl;
    
    //creation d'un integrateur
     IntegrateurEulerCromer I (0.01);

    //faisons avancer le pendule
    unsigned int n (10);
   for (size_t i(0); i < n; ++i){
    cout << "L'integration " << i << " donne : "<<endl;
     I.integre (p);
     p.affiche();
     cout << p.evolution() << "  #accélération" << endl;

 }
     
	/*
	 * ./testPendule | grep '#theta du pendule' > anglependule.txt
	 * gnuplot
	 * plot "anglependule.txt" w linesp
	 * 
	 * ./testPendule | grep '#theta point du pendule' > vitessependule.txt
	 * 
	 * 
set terminal png
set output "evolution_pendule.png"
plot "anglependule.txt" w linesp, "vitessependule.txt" w linesp, "accpendule.txt" w linesp
	 * */
    
    
    /// Faire point_plus_proche et copieobjet() 
    
    
    return 0;
}


